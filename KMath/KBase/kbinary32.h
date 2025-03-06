#ifndef KBINARY32_H
#define KBINARY32_H

#include "King_global.h"

#include <QString>

// 不能表示int最小值
class KING_EXPORT KBinary32
{
public:
    KBinary32(int num = 0);
    KBinary32(bool (&true_form)[]);

    void setInt(int num);

    QString trueForm() const; // 原码
    QString onesComplement() const; // 反码
    QString twosComplement() const; // 补码
    int toInt() const;

private:
    bool true_form_[32];
};

#endif // KBINARY32_H
