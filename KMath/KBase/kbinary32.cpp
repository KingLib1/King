#include "kbinary32.h"

#include <QDebug>

const int WEIGHT[31] = {
    1073741824,
    536870912,
    268435456,
    134217728,
    67108864,
    33554432,
    16777216,
    8388608,
    4194304,
    2097152,
    1048576,
    524288,
    262144,
    131072,
    65536,
    32768,
    16384,
    8192,
    4096,
    2048,
    1024,
    512,
    256,
    128,
    64,
    32,
    16,
    8,
    4,
    2,
    1
};

KBinary32::KBinary32(int num)
{
    setInt(num);
}

void KBinary32::setInt(int num)
{
    if (num < 0) {
        true_form_[0] = 1;
        num = -num;
    } else {
        true_form_[0] = 0;
    }

    int index = 31;
    // 除留余数法
    while (num) {
        true_form_[index--] = num % 2;
        num /= 2;
    }

    for (int i = index; i > 0; --i) // 下标0为符号位，所以不用改
        true_form_[i] = 0;
}

QString KBinary32::trueForm() const
{
    QString code;
    for (int i = 0; i < 32; ++i)
        code.append(true_form_[i] ? '1' : '0');
    return code;
}

QString KBinary32::onesComplement() const
{
    if (!true_form_[0])
        return trueForm();

    QString code;
    code.append('1');
    for (int i = 1; i < 32; ++i)
        code.append(true_form_[i] ? '0' : '1');
    return code;
}

QString KBinary32::twosComplement() const
{
    if (!true_form_[0])
        return trueForm();

    QString code;
    code.append('1');
    int index = 1;
    for (int i = 31; i > 0; --i) {
        if (true_form_[i]) {
            index = i;
            break;
        }
    }

    for (int i = 1; i < index; ++i)
        code.append(true_form_[i] ? '0' : '1');
    for (int i = index; i < 32; ++i)
        code.append(true_form_[i] ? '1' : '0');
    return code;
}

int KBinary32::toInt() const
{
    int value = 0;
    for (int i = 1; i < 32; ++i) {
        if (true_form_[i])
            value += WEIGHT[i - 1];
    }
    if (true_form_[0])
        value = -value;
    return value;
}
