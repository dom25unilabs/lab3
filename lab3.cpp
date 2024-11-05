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
	out_sep(ALIGN_W, LEN);
	for (int i = 0; i < n - 1; i++)
	{
		out_array(ALIGN_W, LEN, names[i], arrs[i]);
		out_sep(ALIGN_W, LEN);
	}
	out_array(ALIGN_W, LEN, names[n - 1], arrs[n - 1]);
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
static void autoui_out_array(int n, double* a)
{
	for (int i = 0; i < n; i++)
	{
		std::wcout << a[i];
		if (i >= n - 1)
		{
			std::wcout << '\n';
		}
		else
		{
			std::wcout << ' ';
		}
	}
}
static void autoui_out_array2(int N, double* a1, double* a2)
{
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		if (a1[i] < 0)
		{
			for (int j = 0; i < cnt; i++)
			{
				std::wcout << "0 ";
			}
			cnt = 0;
			std::wcout << a1[i];
			if (i < N - 1)
			{
				std::wcout << ' ';
			}
			else
			{
				cnt = -2;
			}
		}
		cnt++;
	}
	for (int i = 0; i < N; i++)
	{
		if (a2[i] < 0)
		{
			if (cnt == N)
			{
				cnt = 0;
			}
			else
			{
				std::wcout << ' ';
			}
			for (int j = 0; i < cnt; i++)
			{
				std::wcout << "0 ";
			}
			cnt = 0;
			std::wcout << a2[i];
		}
	}
	if (cnt > 0)
	{
		for (int i = 0; i < cnt - 1; i++)
		{
			std::wcout << "0 ";
		}
		std::wcout << '0';
	}
	std::wcout << '\n';
	cnt = 0;
	for (int i = 0; i < N; i++)
	{
		if (a2[i] > 0)
		{
			for (int j = 0; i < cnt; i++)
			{
				std::wcout << "0 ";
			}
			cnt = 0;
			std::wcout << a2[i];
			if (i < N - 1)
			{
				std::wcout << ' ';
			}
			else
			{
				cnt = -2;
			}
		}
		cnt++;
	}
	for (int i = 0; i < N; i++)
	{
		if (a1[i] > 0)
		{
			if (cnt == N)
			{
				cnt = 0;
			}
			else
			{
				std::wcout << ' ';
			}
			for (int j = 0; i < cnt; i++)
			{
				std::wcout << "0 ";
			}
			cnt = 0;
			std::wcout << a1[i];

		}
	}
	std::wcout << '\n';
}
static void sort(int n, double* a)
{
	int i, j, min_idx;
	for (i = 0; i < n - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[j] < a[min_idx])
			{
				min_idx = j;
			}
		}
		std::swap(a[min_idx], a[i]);
	}
}
static bool isPow2(double x)
{
	long long ix = (long long)x;
	if (ix != x) return 0;
	return ix > 0 && (ix & (ix - 1)) == 0;
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
	double mn[N / M];
	for (int i = 0; i < (N / M); i++)
	{
		mn[i] = INFINITY;
	}
	int idx = -1;
	double a1s[N]{};
	int maxlen = 0;
	for (int i = 0; i < N; i++)
	{
		double v1 = f(x1 + i * step, a, b, c), v2 = f(-x2 + i * step, a, b, c);
		v1 = (abs(v1) < 0.005f ? 0 : v1);
		v2 = (abs(v2) < 0.005f ? 0 : v2);
		if (((aw | bw) & (aw | cw)) == 0)
		{
			a1[i] = std::round(v1);
			a2[i] = std::round(v2);
		}
		else
		{
			a1[i] = std::round(v1 * 100) / 100.0;
			a2[i] = std::round(v2 * 100) / 100.0;
		}
		if (a1[i] < mn[i / M])
		{
			mn[i / M] = a1[i];
		}
		if ((i == 0) || (!isPow2(a1[i])) || (!isPow2(a1[i - 1])) || (a1[i] <= a1[i - 1]))
		{
			idx = i;
		}
		a1s[i] = a1[i];
		if (!autoui)
		{
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
		}
	}
	if (!isPow2(a1[idx]))
	{
		idx = -1;
	}
	sort(N, a1s);
	int cnt = 0;
	for (int i = 1; i < N - 1; i++)
	{
		if (a1s[i - 1] == a1s[i] && a1s[i] != a1s[i + 1])
		{
			cnt++;
		}
	}
	if (a1s[N - 1] == a1s[N - 2])
	{
		cnt++;
	}
	if (autoui)
	{
		autoui_out_array(N, a1);
		autoui_out_array(N, a2);
		for (auto elem : mn)
		{
			std::wcout << elem << '\n';
		}
		autoui_out_array(N, a1s);
		std::wcout << cnt << '\n' << idx << '\n';
		autoui_out_array2(N, a1, a2);
	}
	else
	{
		const int ALIGN_W = maxlen;
		const char* const names[3] = { "a1","a2","a1s" };
		double* arrs[3] = { a1,a2,a1s };
		out_table(ALIGN_W, N, 3, names, arrs);
		for (int i = 0; i < (N / M); i++)
		{
			std::wcout << L"Минимум из подстроки a1[" << i * M << "..." << i * M + M - 1 << "]: " << mn[i] << '\n';
		}
		std::wcout << L"Количество чисел, встречающихся в a1 более одного раза: " << cnt << '\n';
		std::wcout << L"Индекс начала подстроки массива, состоящей из возрастающих степеней двойки: " << idx << '\n';
		double apos[2 * N]{}, aneg[2 * N]{};
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