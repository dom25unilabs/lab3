#include <iostream>
#include <iomanip>
#include <io.h>
#include <fcntl.h>
#include <cmath>
#include <algorithm>
#include <format>
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
static void out_sep(int align_w, int len)
{
	std::wcout << LINE_TBR;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < align_w; j++)
		{
			std::wcout << LINE_LR;
		}
		if (i < len - 1)
		{
			std::wcout << LINE_TLBR;
		}
	}
	std::wcout << LINE_TBL << '\n';
}
static void out_header(int align_w, int len, const char* const* const names, std::wstring format_str_c, std::wstring format_str_r)
{
	std::wcout << LINE_TR;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < align_w; j++)
		{
			std::wcout << LINE_LR;
		}
		if (i < len - 1)
		{
			std::wcout << LINE_BRL;
		}
	}
	std::wcout << LINE_TL << '\n';
	std::wstring wsname(names[0], names[0] + strlen(names[0]));
	std::wcout << std::vformat(format_str_r, std::make_wformat_args(wsname));
	for (int i = 1; i < len; i++)
	{
		std::wstring wsname(names[i], names[i] + strlen(names[i]));
		std::wcout << std::vformat(format_str_c, std::make_wformat_args(wsname));
	}
	std::wcout << LINE_TB << '\n';
}

static void out_table(int align_w, int len, int n, const char* const* const names, double** arrs)
{
	std::wstring format_str_c = std::format(L"{1}{{:^{0}}}", align_w, LINE_TB);
	std::wstring format_str_r = std::format(L"{1}{{:>{0}}}", align_w, LINE_TB);
	out_header(align_w, n, names, format_str_c, format_str_r);
	for (int i = 0; i < len; i++)
	{
		out_sep(align_w, n);
		std::wcout << std::vformat(format_str_r, std::make_wformat_args(arrs[0][i]));
		for (int j = 1; j < n; j++)
		{
			std::wcout << std::vformat(format_str_c, std::make_wformat_args(arrs[j][i]));
		}
		std::wcout << LINE_TB << '\n';
	}
	std::wcout << LINE_BR;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < align_w; j++)
		{
			std::wcout << LINE_LR;
		}
		if (i < n - 1)
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
static void autoui_out_array2(int n, double* a1, double* a2)
{
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		if (a1[i] < 0)
		{
			if (cnt > 0)
			{
				std::wcout << ' ';
			}
			std::wcout << a1[i];
			cnt++;
		}
	}
	for (int i = 0; i < N; i++)
	{
		if (a2[i] < 0)
		{
			if (cnt > 0)
			{
				std::wcout << ' ';
			}
			std::wcout << a2[i];
			cnt++;
		}
	}
	if (cnt < 15)
	{
		if (cnt == 0)
		{
			cnt++;
			std::wcout << '0';
		}
		for (int i = cnt; i < 15; i++)
		{
			std::wcout << " 0";
		}
		cnt = 0;
	}
	std::wcout << '\n';
	cnt = 0;
	for (int i = 0; i < N; i++)
	{
		if (a2[i] > 0)
		{
			if (cnt > 0)
			{
				std::wcout << ' ';
			}
			std::wcout << a2[i];
			cnt++;
		}
	}
	for (int i = 0; i < N; i++)
	{
		if (a1[i] > 0)
		{
			if (cnt > 0)
			{
				std::wcout << ' ';
			}
			std::wcout << a1[i];
			cnt++;
		}
	}
	if (cnt < 15)
	{
		if (cnt == 0)
		{
			cnt++;
			std::wcout << '0';
		}
		for (int i = cnt; i < 15; i++)
		{
			std::wcout << " 0";
		}
		cnt = 0;
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
	bool usewhole = ((((int)a) | ((int)b)) & (((int)a) | ((int)c))) == 0;
	double a1[N]{}, a2[N]{}, raw[N]{};
	double step = (x2 - x1) / (N - 1);
	double mn[N / M]{};
	for (int i = 0; i < (N / M); i++)
	{
		mn[i] = INFINITY;
	}
	int idx = -1;
	double a1s[N]{};
	int maxlen = 0;
	for (int i = 0; i < N; i++)
	{
		raw[i] = x1 + i * step;
		double v1 = f(x1 + i * step, a, b, c), v2 = f(-x2 + i * step, a, b, c);
		v1 = (abs(v1) < 0.005f ? 0 : v1);
		v2 = (abs(v2) < 0.005f ? 0 : v2);
		if (usewhole)
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
		const char* const names[4] = { "X","a1","a2","a1s" };
		double* arrs[4] = { raw,a1,a2,a1s };
		out_table(ALIGN_W, N, 4, names, arrs);
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