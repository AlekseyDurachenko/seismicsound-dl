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
#include "miniseedutils.h"
#include <QObject>
#include <libmseed.h>


bool miniseed_validate(const QString &fileName, QString *reason)
{
    try {
        MSRecord *msr = NULL;
        int retcode = ms_readmsr(&msr, fileName.toLocal8Bit().data(), -1, NULL, NULL, 1, 1, 0);
        if (retcode != MS_NOERROR) {
            throw QString(ms_errorstr(retcode));
        }

        switch (msr->sampletype) {
        case 'i':
        case 'f':
        case 'd':
            break;
        case 'a':
        default:
            throw QObject::tr("unsupported miniseed datatype");
        }

        ms_readmsr(&msr, NULL, 0, NULL, NULL, 0, 0, 0);

        return true;
    }
    catch (const QString &errorString) {
        if (reason) {
            *reason = errorString;
        }
    }

    return false;
}


bool miniseed_samplerate(const QString &fileName, double *samplerate, QString *reason)
{
    try {
        MSRecord *msr = NULL;
        int retcode = ms_readmsr(&msr, fileName.toLocal8Bit().data(), -1, NULL, NULL, 1, 1, 0);
        if (retcode != MS_NOERROR) {
            throw QString(ms_errorstr(retcode));
        }

        if (samplerate) {
            *samplerate = msr_samprate(msr);
        }

        ms_readmsr(&msr, NULL, 0, NULL, NULL, 0, 0, 0);

        return true;
    }
    catch (const QString &errorString) {
        if (reason) {
            *reason = errorString;
        }
    }

    return false;
}


qint64 miniseed_samplecount(const QString &fileName, QString *reason)
{
    try {
        qint64 count = 0;
        MSRecord *msr = NULL;
        while (true) {
            int retcode = ms_readmsr(&msr, fileName.toLocal8Bit().data(), -1, NULL, NULL, 1, 1, 0);
            if (retcode != MS_NOERROR) {
                break;
            }

            switch (msr->sampletype) {
            case 'i':
            case 'f':
            case 'd':
                count += msr->samplecnt;
                break;
            case 'a':
            default:
                throw QObject::tr("unsupported miniseed datatype");
            }
        }

        ms_readmsr(&msr, NULL, 0, NULL, NULL, 0, 0, 0);

        return count;
    }
    catch (const QString &errorString) {
        if (reason) {
            *reason = errorString;
        }
    }

    return -1;
}


bool miniseed_to_datasamples(const QString &fileName,
                             const QDateTime &startTime,
                             float *datasamples,
                             qint64 samplecnt,
                             QString *reason)
{
    try {
        MSRecord *msr = NULL;
        int retcode = MS_ENDOFFILE;
        hptime_t hpStartTime = MS_EPOCH2HPTIME(startTime.toTime_t());
        double absMax = 0.0;
        double avg = 0.0;
        qint64 avgElementCount = 0;

        while (true) {
            retcode = ms_readmsr(&msr, fileName.toLocal8Bit().data(), -1, NULL, NULL, 1, 1, 0);
            if (retcode != MS_NOERROR) {
                break;
            }

            const qint64 firstSample = qRound64((msr_starttime(msr) - hpStartTime) / 1000000.0 * msr_samprate(msr));
            if (firstSample < 0 || firstSample >= samplecnt) {
                continue;
            }

            if (msr->sampletype == 'a') {
                throw QObject::tr("unsupported miniseed datatype");
            }
            else if (msr->sampletype == 'i') {
                for (qint64 i = 0; i < msr->numsamples && i + firstSample < samplecnt; ++i) {
                    datasamples[i + firstSample] = reinterpret_cast<int *>(msr->datasamples)[i];
                    avg += reinterpret_cast<int *>(msr->datasamples)[i];
                    avgElementCount += 1;
                }
            }
            else if (msr->sampletype == 'f') {
                for (qint64 i = 0; i < msr->numsamples && i + firstSample < samplecnt; ++i) {
                    datasamples[i + firstSample] = reinterpret_cast<float *>(msr->datasamples)[i];
                    avg += reinterpret_cast<float *>(msr->datasamples)[i];
                    avgElementCount += 1;
                }
            }
            else if (msr->sampletype == 'd') {
                for (qint64 i = 0; i < msr->numsamples && i + firstSample < samplecnt; ++i) {
                    datasamples[i + firstSample] = reinterpret_cast<double *>(msr->datasamples)[i];
                    avg += reinterpret_cast<double *>(msr->datasamples)[i];
                    avgElementCount += 1;
                }
            }
        }

        ms_readmsr(&msr, NULL, 0, NULL, NULL, 0, 0, 0);
        if (retcode != MS_ENDOFFILE) {
            throw QString(ms_errorstr(retcode));
        }

        avg /= avgElementCount;
        for (qint64 i = 0; i < samplecnt; ++i) {
            datasamples[i] -= avg;
            if (qAbs(datasamples[i]) > absMax) {
                absMax = qAbs(datasamples[i]);
            }
        }

        for (qint64 i = 0; i < samplecnt; ++i) {
            datasamples[i] /= absMax;
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
