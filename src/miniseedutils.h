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
#ifndef MINISEEDUTILS_H
#define MINISEEDUTILS_H


#include <QDateTime>

bool miniseed_validate(const QString &fileName,
                       QString *reason = 0);

bool miniseed_samplerate(const QString &fileName,
                         double *samplerate,
                         QString *reason = 0);

// returns -1 if error or number of samples
qint64 miniseed_samplecount(const QString &fileName,
                            QString *reason = 0);

bool miniseed_to_datasamples(const QString &fileName,
                             const QDateTime &startTime,
                             float *datasamples,
                             qint64 samplecnt,
                             QString *reason = 0);

bool miniseed_to_datasamples_skip_gap(const QString &fileName,
                                      float *datasamples,
                                      qint64 samplecnt,
                                      QString *reason = 0);


#endif // MINISEEDUTILS_H
