// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Copyright (c) 2017 The KekCoinSignSignature Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KEKCOIN_SCRIPT_SIGN_H
#define KEKCOIN_SCRIPT_SIGN_H

#include "script/interpreter.h"
#include "script/standard.h"

class CKeyID;
class CKeyStore;
class CScript;
class CTransaction;

struct CMutableTransaction;

/** Virtual base class for signature creators. */
class BaseSignatureCreator {
protected:
    const CKeyStore* keystore;

public:
    BaseSignatureCreator(const CKeyStore* keystoreIn) : keystore(keystoreIn) {}
    const CKeyStore& KeyStore() const { return *keystore; };
    virtual ~BaseSignatureCreator() {}
    virtual const BaseSignatureChecker& Checker() const =0;

    /** Create a singular (non-script) signature. */
    virtual bool CreateSig(std::vector<unsigned char>& vchSig, const CKeyID& keyid, const CScript& scriptCode, SigVersion sigversion) const =0;
};

/** A signature creator for transactions. */
class TransactionSignatureCreator : public BaseSignatureCreator {
    const CTransaction* txTo;
    unsigned int nIn;
    int nHashType;
    CAmount amount;
    const TransactionSignatureChecker checker;

public:
    TransactionSignatureCreator(const CKeyStore* keystoreIn, const CTransaction* txToIn, unsigned int nInIn, const CAmount& amountIn, int nHashTypeIn=SIGHASH_ALL);
    const BaseSignatureChecker& Checker() const { return checker; }
    bool CreateSig(std::vector<unsigned char>& vchSig, const CKeyID& keyid, const CScript& scriptCode, SigVersion sigversion) const;
};

class MutableTransactionSignatureCreator : public TransactionSignatureCreator {
    CTransaction tx;

public:
    MutableTransactionSignatureCreator(const CKeyStore* keystoreIn, const CMutableTransaction* txToIn, unsigned int nInIn, const CAmount& amount, int nHashTypeIn) : TransactionSignatureCreator(keystoreIn, &tx, nInIn, amount, nHashTypeIn), tx(*txToIn) {}
};

/** A signature creator that just produces 72-byte empty signatyres. */
class DummySignatureCreator : public BaseSignatureCreator {
public:
    DummySignatureCreator(const CKeyStore* keystoreIn) : BaseSignatureCreator(keystoreIn) {}
    const BaseSignatureChecker& Checker() const;
    bool CreateSig(std::vector<unsigned char>& vchSig, const CKeyID& keyid, const CScript& scriptCode, SigVersion sigversion) const;
};

struct SignatureData {
    CScript scriptSig;
    CScriptWitness scriptWitness;

    SignatureData() {}
    explicit SignatureData(const CScript& script) : scriptSig(script) {}
};

/** Produce a script signature using a generic signature creator. */
bool ProduceSignature(const BaseSignatureCreator& creator, const CScript& scriptPubKey, SignatureData& sigdata);

/** Produce a script signature for a transaction. */
bool SignSignature(const CKeyStore &keystore, const CScript& fromPubKey, CTransaction& txTo, unsigned int nIn, const CAmount& amount, int nHashType=SIGHASH_ALL);
bool SignSignature(const CKeyStore& keystore, const CTransaction& txFrom, CMutableTransaction& txTo, unsigned int nIn, int nHashType=SIGHASH_ALL);
bool SignNoMutableSignature(const CKeyStore &keystore, const CScript& fromPubKey, CTransaction& txTo, unsigned int nIn, const CAmount& amount, int nHashType=SIGHASH_ALL);
bool SignNoMutableSignature(const CKeyStore& keystore, const CTransaction& txFrom, CTransaction& txTo, unsigned int nIn, int nHashType=SIGHASH_ALL);

bool SignSignatureKekcoin(const CKeyStore& keystore, const CScript& fromPubKey, CMutableTransaction& txTo, unsigned int nIn, int nHashType=SIGHASH_ALL);
bool SignSignatureKekcoin(const CKeyStore &keystore, const CTransaction& txFrom, CMutableTransaction& txTo, unsigned int nIn, int nHashType=SIGHASH_ALL);
bool VerifyScriptKekcoin(const CScript& scriptSig, const CScript& scriptPubKey, const CTransaction& txTo, unsigned int nIn, unsigned int flags, int nHashType);
bool VerifyScriptKekcoin(const CScript& scriptSig, const CScript& scriptPubKey, unsigned int flags, const BaseSignatureCheckerKekcoin& checker, ScriptError* error = NULL);

bool SolverKekcoin(const CScript& scriptPubKey, txnouttype& typeRet, std::vector<std::vector<unsigned char> >& vSolutionsRet);
bool SolverKekcoin(const CKeyStore& keystore, const CScript& scriptPubKey, uint256 hash, int nHashType,
CScript& scriptSigRet, txnouttype& whichTypeRet);


/** Combine two script signatures using a generic signature checker, intelligently, possibly with OP_0 placeholders. */
SignatureData CombineSignatures(const CScript& scriptPubKey, const BaseSignatureChecker& checker, const SignatureData& scriptSig1, const SignatureData& scriptSig2);

/** Extract signature data from a transaction, and insert it. */
SignatureData DataFromTransaction(const CMutableTransaction& tx, unsigned int nIn);
void UpdateTransaction(CMutableTransaction& tx, unsigned int nIn, const SignatureData& data);
void UpdateNoMutableTransaction(CTransaction& tx, unsigned int nIn, const SignatureData& data);

#endif // KEKCOIN_SCRIPT_SIGN_H
