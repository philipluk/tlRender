// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tlrQt/TimelineThumbnailProvider.h>

#include <tlrCore/IRender.h>
#include <tlrCore/TimelinePlayer.h>

#include <QAbstractTableModel>

namespace tlr
{
    //! Files model item.
    struct FilesModelItem
    {
        file::Path path;
        file::Path audioPath;

        bool init = false;

        otime::RationalTime duration = time::invalidTime;
        otime::RationalTime globalStartTime = time::invalidTime;
        avio::Info avInfo;

        double speed = 0.0;
        timeline::Playback playback = timeline::Playback::Stop;
        timeline::Loop loop = timeline::Loop::Loop;
        otime::RationalTime currentTime = time::invalidTime;
        otime::TimeRange inOutRange = time::invalidTimeRange;

        uint16_t videoLayer = 0;

        float volume = 0.F;
        bool mute = false;
        double audioOffset = 0.0;

        render::ImageOptions imageOptions;
    };

    //! Files model.
    class FilesModel : public QAbstractTableModel
    {
        Q_OBJECT

    public:
        FilesModel(
            const std::shared_ptr<core::Context>&,
            QObject* parent = nullptr);

        const render::CompareOptions& compareOptions() const;

        const std::vector<std::shared_ptr<FilesModelItem> >& items() const;

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;
        Qt::ItemFlags flags(const QModelIndex&) const override;
        QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const override;
        bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    public Q_SLOTS:
        void add(const std::shared_ptr<FilesModelItem>&);
        void close();
        void closeAll();

        void setA(int index);
        void setB(int index, bool);

        void first();
        void last();
        void next();
        void prev();

        void setLayer(const std::shared_ptr<FilesModelItem>&, int layer);

        void setImageOptions(const tlr::render::ImageOptions&);

        void setCompareOptions(const tlr::render::CompareOptions&);

    Q_SIGNALS:
        void countChanged(int);

        void activeChanged(const std::vector<std::shared_ptr<FilesModelItem> >&);

        void layerChanged(const std::shared_ptr<FilesModelItem>&, int layer);

        void imageOptionsChanged(const std::vector<tlr::render::ImageOptions>&);

        void compareOptionsChanged(const tlr::render::CompareOptions&);

    private Q_SLOTS:
        void _thumbailCallback(const QList<QPair<otime::RationalTime, QImage> >&);

    private:
        int _index(const std::shared_ptr<FilesModelItem>&) const;
        std::vector<int> _bIndexes() const;
        std::vector<std::shared_ptr<FilesModelItem> > _active() const;
        std::vector<render::ImageOptions> _imageOptions() const;

        std::weak_ptr<core::Context> _context;

        std::vector<std::shared_ptr<FilesModelItem> > _items;
        std::shared_ptr<FilesModelItem> _a;
        std::vector<std::shared_ptr<FilesModelItem> > _b;
        render::CompareOptions _compareOptions;

        std::map<std::shared_ptr<FilesModelItem>, QImage> _thumbnails;
        std::map<std::shared_ptr<FilesModelItem>, qt::TimelineThumbnailProvider*> _thumbnailProviders;
    };
}