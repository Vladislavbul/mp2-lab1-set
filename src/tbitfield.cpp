// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) // Длина не может быть отрицательной
	{
		throw "Error when create bitfield";
	}
	BitLen = len;
	MemLen = (BitLen + 31) / 32; // Кол-во ячеек
    pMem = new TELEM[MemLen]; // Выделение памяти
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen]; // Выделение памяти
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / 32);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return (1 << (n % 32));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n > BitLen) // Проверка на отрицание и превышение номера бита
	{
		throw "Error when set bit";
	}
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > BitLen) // Проверка на отрицание и превышение номера бита
	{
		throw "Error when set bit";
	}
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > BitLen) // Проверка на отрицание и превышение номера бита
	{
		throw "Error when set bit";
	}
	return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (&bf == this) // Проверка на самоприсваивание
	{
		return *this;
	}
	delete[] pMem;
	BitLen = bf.BitLen; // длина
	MemLen = bf.MemLen; // кол-во ячеек
	pMem = new TELEM[MemLen]; // выделение памяти
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (bf.BitLen != BitLen) // сравниваем размеры массивов
	{
		return 0;
	}
	else // проверяем данные в массивах
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i]) return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (bf.BitLen == BitLen) // сравниваем размеры массивов
	{
		for (int i = 0; i < MemLen; i++) // проверяем данные в массивах
		{
			if (pMem[i] == bf.pMem[i]) return 0;
		}
	}
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int lenght = BitLen;
	if (bf.BitLen > lenght)
	{
		lenght = bf.BitLen;
	}
	TBitField temp(lenght);
	for (int i = 0; i < MemLen; i++)
	{
		temp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		temp.pMem[i] |= bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int lenght = BitLen;
	if (bf.BitLen > lenght)
	{
		lenght = bf.BitLen;
	}
	TBitField temp(lenght);
	for (int i = 0; i < MemLen; i++)
	{
		temp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		temp.pMem[i] &= bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int lenght = BitLen;
	TBitField temp(lenght);
	for (int i = 0; i < lenght; i++)
	{
		if (GetBit(i) == 0)
		{
			temp.SetBit(i);
		}
		else
		{
			temp.ClrBit(i);
		}
	}
	return temp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int i = 0;
	char ch;
	do
	{
		istr >> ch;
	}
	while (ch != ' ');

	while (1)
	{
		istr >> ch;
		if (ch == '0')
		{
			bf.ClrBit(i++);
		}
		else
			if (ch == '1')
			{
				bf.SetBit(i++);
			}
			else
			{
				break;
			}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int lenght = bf.GetLength();
	for (int i = 0; i < lenght; i++)
	{
		if (bf.GetBit(i))
		{
			ostr << '1';
		}
		else
		{
			ostr << '0';
		}
	}
	return ostr;
}
