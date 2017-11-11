// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KEKCOIN_QT_KEKCOINADDRESSVALIDATOR_H
#define KEKCOIN_QT_KEKCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class KekCoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KekCoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** KekCoin address widget validator, checks for a valid kekcoin address.
 */
class KekCoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KekCoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // KEKCOIN_QT_KEKCOINADDRESSVALIDATOR_H
