#include <iostream>
#include <iomanip>
#include <io.h>
#include <fcntl.h>
#include <cmath>
#include <algorithm>
constexpr int N = 15, M = 5;
constexpr wchar_t LINE_LR = L'\u2550';
constexpr wchar_t LINE_TB = L'\u2551';
constexpr wchar_t LINE_TR = L'\u2554';
constexpr wchar_t LINE_TL = L'\u2557';
constexpr wchar_t LINE_BR = L'\u255A';
constexpr wchar_t LINE_BL = L'\u255D';
constexpr wchar_t LINE_TBR = L'\u2560';
constexpr wchar_t LINE_TBL = L'\u2563';
constexpr wchar_t LINE_BRL = L'\u2566';
constexpr wchar_t LINE_TRL = L'\u2569';
constexpr wchar_t LINE_TLBR = L'\u256C';
static void out_sep(int ALIGN_W, int LEN)
{
	std::wcout << '\n' << LINE_TBR;
	for (int i = 0; i < LEN + 1; i++)
	{
		for (int j = 0; j < ALIGN_W; j++)
		{
			std::wcout << LINE_LR;
		}
		if (i < LEN)
		{
			std::wcout << LINE_TLBR;
		}
	}

}

static void out_array(int ALIGN_W, int LEN, const char* const name, double* a)
{
	std::wcout << LINE_TBL << '\n' << LINE_TB;
	std::wcout << std::left << std::setw(ALIGN_W) << std::setfill(L' ') << name;
	std::wcout << LINE_TB;
	for (int i = 0; i < LEN; i++)
	{
		std::wcout << std::right << std::setw(ALIGN_W) << std::setfill(L' ') << a[i];
		std::wcout << LINE_TB;
	}
}

static void out_table(int ALIGN_W, int LEN, int n, const char* const* const names, double** arrs)
{
	std::wcout << LINE_TR;
	for (int i = 0; i < LEN + 1; i++)
	{
		for (int j = 0; j < ALIGN_W; j++)
		{
			std::wcout << LINE_LR;
		}
		if (i < LEN)
		{
			std::wcout << LINE_BRL;
		}
	}
	std::wcout << LINE_TL << '\n' << LINE_TB;
	std::wcout << std::left << std::setw(ALIGN_W) << std::setfill(L' ') << "idx";
	std::wcout << LINE_TB;
	for (int i = 0; i < LEN; i++)
	{
		std::wcout << std::left << std::setw(ALIGN_W) << std::setfill(L' ') << i;
		std::wcout << LINE_TB;
	}
	out_sep(ALIGN_W,LEN);
	for (int i = 0; i < n - 1; i++)
	{
		out_array(ALIGN_W,LEN, names[i], arrs[i]);
		out_sep(ALIGN_W,LEN);
	}
	out_array(ALIGN_W,LEN, names[n - 1], arrs[n - 1]);
	std::wcout << '\n' << LINE_BR;
	for (int i = 0; i < LEN + 1; i++)
	{
		for (int j = 0; j < ALIGN_W; j++)
		{
			std::wcout << LINE_LR;
		}
		if (i < LEN)
		{
			std::wcout << LINE_TRL;
		}
	}
	std::wcout << LINE_BL << '\n';
}
bool isPow2(double x)
{
	int exponent = 0;
	auto mantissa1 = frexp(x, &exponent);
	return mantissa1 == 0.5;
}

static double f(double x, double a, double b, double c)
{
	if (x < 0 && b != 0)
	{
		return a * x * x + b;
	}
	else if (x > 0 && b == 0)
	{
		return (x - a) / (x - c);
	}
	else
	{
		return x / c;
	}
}
int wmain(int argc, wchar_t* argv[])
{
	if (!(_setmode(_fileno(stdout), _O_U8TEXT) && _setmode(_fileno(stdin), _O_U8TEXT) && _setmode(_fileno(stderr), _O_U8TEXT)))
		return 1;
	bool autoui = true;
	if (argc <= 1 || std::wcsncmp(argv[1], L"false", sizeof(L"false") - 1) != 0)
	{
		autoui = false;
	}
	double x1, x2, a, b, c;
	std::wcin >> x1 >> x2 >> a >> b >> c;
	int aw = a, bw = b, cw = c;
	double a1[N]{}, a2[N]{};
	double step = (x2 - x1 + 1) / N;
	double mn[N / M]{ };
	int idx = 0;
	double a1s[N]{};
	int maxlen = 0;
	for (int i = 0; i < N; i++)
	{
		if (((aw | bw) & (aw | cw)) == 0)
		{
			a1[i] = std::round(f(x1 + i * step, a, b, c));
			a2[i] = std::round(f(-x2 + i * step, a, b, c));

		}
		else
		{
			a1[i] = std::round(f(x1 + i * step, a, b, c) * 100) / 100.0;
			a2[i] = std::round(f(-x2 + i * step, a, b, c) * 100) / 100.0;
		}
		int len = std::snprintf(nullptr, 0, "%.2f", a1[i]);
		if (len > maxlen)
		{
			maxlen = len;
		}
		len = std::snprintf(nullptr, 0, "%.2f", a2[i]);
		if (len > maxlen)
		{
			maxlen = len;
		}
		if (i % (N / M) == 0 || a1[i] < mn[i / M])
		{
			mn[i / M] = a1[i];
		}
		if ((i == 0) || (!(isPow2(a1[i]) && isPow2(a1[i-1]))))
		{
			idx = -1;
			if (isPow2(a1[i]))
			{
				idx = i;
			}
		}
		a1s[i] = a1[i];
	}
	std::sort(std::begin(a1s), std::end(a1s));
	double cur = 0;
	int cnt = 0;
	const int ALIGN_W = maxlen;
	for (int i = 0; i < N; i++)
	{
		if (i > 0 && a1s[i] == a1s[i - 1] && a1s[i] != cur)
		{
			cur = a1s[i];
			cnt++;
		}
	}
	if (autoui)
	{
		for (int i = 0; i < N; i++)
		{
			std::wcout << a1[i];
			if (i >= N - 1)
			{
				std::wcout << '\n';
			}
			else
			{
				std::wcout << ' ';
			}
		}
		for (int i = 0; i < N; i++)
		{
			std::wcout << a2[i];
			if (i >= N - 1)
			{
				std::wcout << '\n';
			}
			else
			{
				std::wcout << ' ';
			}
		}
		for (auto elem : mn)
		{
			std::wcout << elem << '\n';
		}
		for (int i = 0; i < N; i++)
		{
			std::wcout << a1s[i];
			if (i >= N - 1)
			{
				std::wcout << '\n';
			}
			else
			{
				std::wcout << ' ';
			}
		}
		std::wcout << cnt << '\n' << idx << '\n';
		cnt = -1;
		for (int i = 0; i < N; i++)
		{
			if (a1[i] < 0)
			{
				for (int j = 0; i < cnt; i++)
				{
					std::wcout << "0 ";
				}
				std::wcout << a1[i];
				if (i < N - 1)
				{
					std::wcout << ' ';
				}
			}
		}
		for (int i = 0; i < N; i++)
		{
			if (a2[i] < 0)
			{
				for (int j = 0; i < cnt; i++)
				{
					std::wcout << "0 ";
				}
				if (cnt != -1)
				{
					std::wcout << ' ';
					cnt = 0;
				}
				std::wcout << a2[i];
				if (i < N - 1)
				{
					std::wcout << ' ';
				}
			}
		}
		std::wcout << '\n';
		cnt = -1;
		for (int i = 0; i < N; i++)
		{
			if (a2[i] > 0)
			{
				for (int j = 0; i < cnt; i++)
				{
					std::wcout << "0 ";
				}
				std::wcout << a2[i];
				if (i < N - 1)
				{
					std::wcout << ' ';
				}
			}
		}
		for (int i = 0; i < N; i++)
		{
			if (a1[i] > 0)
			{
				for (int j = 0; i < cnt; i++)
				{
					std::wcout << "0 ";
				}
				if (cnt != -1)
				{
					std::wcout << ' ';
					cnt = 0;
				}
				std::wcout << a1[i];
				if (i < N - 1)
				{
					std::wcout << ' ';
				}
			}
		}
	}
	else
	{
		const char* const names[3] = { "a1","a2","a1s" };
		double* arrs[3] = { a1,a2,a1s };
		out_table(ALIGN_W, N, 3, names, arrs);
		for (auto elem : mn)
		{
			std::wcout << elem << '\n';
		}
		std::wcout << cnt << '\n' << idx << '\n';
		double apos[2 * N]{}, aneg[30]{};
		for (int i = 0; i < N; i++)
		{
			apos[i] = std::max(a1[i], 0.0);
			aneg[i] = std::min(a2[i], 0.0);
		}
		for (int i = 0; i < N; i++)
		{
			apos[N + i] = std::max(a2[i], 0.0);
			aneg[N + i] = std::min(a1[i], 0.0);
		}
		const char* const names2[2] = { "pos","neg" };
		double* arrs2[2] = { apos,aneg };
		out_table(ALIGN_W, 2 * N, 2, names2, arrs2);
	}
}