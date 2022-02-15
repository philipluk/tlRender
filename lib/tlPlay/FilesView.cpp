// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#include <tlPlay/FilesView.h>

#include <QComboBox>

namespace tl
{
    namespace play
    {
        FilesLayersItemDelegate::FilesLayersItemDelegate(QObject* parent) :
            QStyledItemDelegate(parent),
            _mapper(new QSignalMapper(this))
        {
            connect(
                _mapper,
                SIGNAL(mappedObject(QObject*)),
                SLOT(_mapperCallback(QObject*)));
        }

        QWidget* FilesLayersItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& options, const QModelIndex& index) const
        {
            QComboBox* out = new QComboBox(parent);
            if (auto model = qobject_cast<const FilesTableModel*>(index.model()))
            {
                const auto& files = model->files();
                if (index.isValid() &&
                    index.row() >= 0 &&
                    index.row() < files.size())
                {
                    for (const auto& video : files[index.row()]->avInfo.video)
                    {
                        out->addItem(QString::fromUtf8(video.name.c_str()));
                    }
                }
            }
            connect(
                out,
                SIGNAL(activated(int)),
                _mapper,
                SLOT(map()));
            _mapper->setMapping(out, out);
            return out;
        }

        void FilesLayersItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
        {
            QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
            comboBox->setCurrentIndex(index.data(Qt::EditRole).toInt());
        }

        void FilesLayersItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
        {
            QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
            model->setData(index, comboBox->currentIndex(), Qt::EditRole);
        }

        void FilesLayersItemDelegate::_mapperCallback(QObject* value)
        {
            Q_EMIT commitData(qobject_cast<QWidget*>(value));
        }
    }
}