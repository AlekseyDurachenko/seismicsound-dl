// Copyright 2017, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "dataselect.h"
#include "urldownloader.h"
#include "miniseedutils.h"
#include <sndfile.h>
#include <QTemporaryFile>


static sf_count_t vio_get_filelen(void *user_data)
{
    return static_cast<QIODevice *>(user_data)->size();
}


static sf_count_t vio_seek(sf_count_t offset, int whence, void *user_data)
{
    sf_count_t pos = 0;
    switch (whence) {
    case SEEK_SET :
        pos = offset;
        break;
    case SEEK_CUR :
        pos = static_cast<QIODevice *>(user_data)->pos() + offset;
        break;
    case SEEK_END :
        pos = static_cast<QIODevice *>(user_data)->size() - offset;
        break;
    default :
        pos = 0;
        break;
    }

    return static_cast<QIODevice *>(user_data)->seek(pos);
}


static sf_count_t vio_read(void *ptr, sf_count_t count, void *user_data)
{
    return static_cast<QIODevice *>(user_data)->read(static_cast<char *>(ptr), count);
}


static sf_count_t vio_write(const void *ptr, sf_count_t count, void *user_data)
{
    return static_cast<QIODevice *>(user_data)->write(static_cast<const char *>(ptr), count);
}


static sf_count_t vio_tell(void *user_data)
{
    return static_cast<QIODevice *>(user_data)->pos();
}


struct SndFileDeleter {
    static inline void cleanup(SNDFILE *sndfile)
    {
        sf_close(sndfile);
    }
};


bool dataselect_and_save_sound(const AppArguments &arguments,
                               const DataSelectQuery &query,
                               const QString &fileName,
                               const SoundTags &tags,
                               QString *reason)
{
    try {
        // temporary miniseed file
        QTemporaryFile miniseedFile;
        miniseedFile.setAutoRemove(true);
        if (!miniseedFile.open()) {
            throw miniseedFile.errorString();
        }

        // download the miniseed data
        UrlDownloader urlDownloader;
        if (urlDownloader.download(query.buildQueryUrl(), &miniseedFile, reason) != UrlDownloader::NoError) {
            return false;
        }

        // sync before open the file with libmseed
        if (!miniseedFile.flush()) {
            throw miniseedFile.errorString();
        }

        // if miniseed file size too small miniseed data not found at the time
        //if (miniseedFile.size() < 4096) {
        //    throw QObject::tr("the trace is empty (possible, station was off at specified time)");
        //}

        // validate the miniseed file
        if (!miniseed_validate(miniseedFile.fileName(), reason)) {
            return false;
        }

        // calculate actual sample count
        const qint64 samplecount = miniseed_samplecount(miniseedFile.fileName(), reason);
        if (samplecount < 0) {
            return false;
        }
        else if (samplecount == 0) {
            throw QObject::tr("the trace is empty (possible, station was off at specified time)");
        }

        // read sample rate for array size calculating
        double samplerate = 0.0;
        if (!miniseed_samplerate(miniseedFile.fileName(), &samplerate, reason)) {
            return false;
        }

        // temporary file for unpack the miniseed data
        QTemporaryFile datasamplesFile;
        datasamplesFile.setAutoRemove(true);
        if (!datasamplesFile.open()) {
            throw datasamplesFile.errorString();
        }

        // calculate actual sample count
        //const qint64 samplecount = static_cast<qint64>(query.startTime().secsTo(query.endTime()) * samplerate);

        // resize the file for store the all datasamples
        if (!datasamplesFile.resize(samplecount * sizeof(float))) {
            throw datasamplesFile.errorString();
        }

        // file memory mapping
        float *datasamples = reinterpret_cast<float *>(datasamplesFile.map(0, samplecount * sizeof(float)));
        if (!datasamples) {
            throw datasamplesFile.errorString();
        }

        // read the datasamples from miniseed to the datasamples array
        //if (!miniseed_to_datasamples(miniseedFile.fileName(),
        //                             query.startTime(),
        //                             datasamples,
        //                             samplecount,
        //                             reason)) {
        //    return false;
        //}

        // read the datasamples from miniseed to the datasamples array without
        // any gap and time control, usefull for data with many small gaps
        if (!miniseed_to_datasamples_skip_gap(miniseedFile.fileName(),
                                              datasamples,
                                              samplecount,
                                              reason)) {
            return false;
        }


        // try to open file for write the wav file
        QFile soundFile(fileName);
        if (!soundFile.open(QIODevice::WriteOnly)) {
            throw soundFile.errorString();
        }

        SF_VIRTUAL_IO vio;
        vio.get_filelen = &vio_get_filelen;
        vio.read = &vio_read;
        vio.seek = &vio_seek;
        vio.tell = &vio_tell;
        vio.write = &vio_write;

        SF_INFO info;
        info.frames = samplecount;
        info.samplerate = arguments.sampleRate();
        info.channels = 1;
        info.sections = 0;
        info.seekable = 0;
        info.format = arguments.sampleFormat();

        // open sound file for write
        QScopedPointer<SNDFILE, SndFileDeleter> sndfile(sf_open_virtual(&vio, SFM_WRITE, &info, &soundFile));
        if (sndfile == NULL) {
            if (soundFile.errorString().isEmpty()) {
                throw QString(sf_strerror(sndfile.data()));
            }

            throw soundFile.errorString();
        }

        // write the metadata informat-lsndfileion
        sf_set_string(sndfile.data(), SF_STR_TITLE,
                      tags.title().toUtf8().data());
        sf_set_string(sndfile.data(), SF_STR_COPYRIGHT,
                      tags.copyright().toUtf8().data());
        sf_set_string(sndfile.data(), SF_STR_SOFTWARE,
                      tags.software().toUtf8().data());
        sf_set_string(sndfile.data(), SF_STR_ARTIST,
                      tags.artist().toUtf8().data());
        sf_set_string(sndfile.data(), SF_STR_COMMENT,
                      tags.comment().toUtf8().data());
        sf_set_string(sndfile.data(), SF_STR_DATE,
                      tags.date().toUtf8().data());
        sf_set_string(sndfile.data(), SF_STR_GENRE,
                      tags.genre().toUtf8().data());

        // write to the file
        if (sf_writef_float(sndfile.data(), datasamples, samplecount) != samplecount) {
            if (soundFile.errorString().isEmpty()) {
                throw QString(sf_strerror(sndfile.data()));
            }

            throw soundFile.errorString();
        }

        return true;
    }
    catch (const QString &errorString) {
        if (reason) {
            *reason = errorString;
        }
    }

    return false;
}
