#ifndef COMBOBOXHELPER_H
#define COMBOBOXHELPER_H

#endif // COMBOBOXHELPER_H
#pragma once

#include <QComboBox>
#include <QObject>
#include <functional>

namespace ComboBoxHelper {

template <typename ValueType>
struct Item
{
    Item(const QString &text, const ValueType &value)
        : text(text)
        , value(value)
    {
    }
    QString text;
    ValueType value;
};

template <typename ValueType>
void setup(QComboBox *cb, ValueType defaultValue, const QVector<Item<ValueType>> &list,
           const std::function<void(ValueType)> &function = {})
{
    for (const Item<ValueType> &item : list) {
        cb->addItem(item.text, QVariant::fromValue(item.value));
        if (item.value == defaultValue) {
            cb->setCurrentIndex(cb->count() - 1);
        }
    }
    if (function) {
        QObject::connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged), [function, cb] {
            const ValueType value = cb->currentData().value<ValueType>();
            function(value);
        });
        function(defaultValue);
    }
}

template <typename ValueType, typename Target, typename Function>
void setup(QComboBox *cb, ValueType defaultValue, const QVector<Item<ValueType>> &list,
           Target *target, Function function)
{
    setup(cb, defaultValue, list);
    QObject::connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [function, cb, target] {
                         const ValueType value = cb->currentData().value<ValueType>();
                         std::invoke(function, target, value);
                     });
    std::invoke(function, target, defaultValue);
}
}
