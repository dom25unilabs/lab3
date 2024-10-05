#include <iostream>
#include <iomanip>
#include <io.h>
#include <fcntl.h>
#include <cmath>
#include <algorithm>
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
constexpr int N = 15, M = 5;
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
		if ((i == 0) || (a1[i] != 2 * a1[i - 1]))
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
	if (!autoui)
	{
		std::wcout << L'\u2554';
		for (int i = 0; i < N+1; i++)
		{
			for (int j = 0; j < ALIGN_W; j++)
			{
				std::wcout << L'\u2550';
			}
			if (i < N)
			{
				std::wcout << L'\u2566';
			}
		}
		std::wcout << L'\u2557' << '\n' << L'\u2551';
		std::wcout << std::left << std::setw(ALIGN_W) << std::setfill(L' ') << "idx";
		std::wcout << L'\u2551';
		for (int i = 0; i < N; i++)
		{
			std::wcout << std::left << std::setw(ALIGN_W) << std::setfill(L' ') << i;
			std::wcout << L'\u2551';
		}
		std::wcout << '\n' << L'\u2560';
		for (int i = 0; i < N+1; i++)
		{
			for (int j = 0; j < ALIGN_W; j++)
			{
				std::wcout << L'\u2550';
			}
			if (i < N)
			{
				std::wcout << L'\u256C';
			}
		}
		std::wcout << L'\u2563' << '\n' << L'\u2551';
		std::wcout << std::left << std::setw(ALIGN_W) << std::setfill(L' ') << "a1";
		std::wcout << L'\u2551';
	}
	for (int i = 0; i < N; i++)
	{
		if (i > 0 && a1s[i] == a1s[i - 1] && a1s[i] != cur)
		{
			cur = a1s[i];
			cnt++;
		}
		if (autoui)
		{
			std::wcout << a1[i];
			if (i < N - 1)
			{
				std::wcout << ' ';
			}
		}
		else
		{
			std::wcout << std::right << std::setw(ALIGN_W) << std::setfill(L' ') << a1[i];
			std::wcout << L'\u2551';
		}
	}
	if (!autoui) 
	{
		std::wcout << '\n' << L'\u2560';
		for (int i = 0; i < N + 1; i++)
		{
			for (int j = 0; j < ALIGN_W; j++)
			{
				std::wcout << L'\u2550';
			}
			if (i < N)
			{
				std::wcout << L'\u256C';
			}
		}
		std::wcout << L'\u2563' << '\n' << L'\u2551';
		std::wcout << std::left << std::setw(ALIGN_W) << std::setfill(L' ') << "a2";
		std::wcout << L'\u2551';
	}
	for (int i = 0; i < N; i++)
	{
		if (autoui)
		{
			std::wcout << a2[i];
			if (i < N - 1)
			{
				std::wcout << ' ';
			}
		}
		else
		{
			std::wcout << std::right << std::setw(ALIGN_W) << std::setfill(L' ') << a2[i];
			std::wcout << L'\u2551';
		}
	}
	if (!autoui)
	{
		std::wcout << '\n' << L'\u2560';
		for (int i = 0; i < N + 1; i++)
		{
			for (int j = 0; j < ALIGN_W; j++)
			{
				std::wcout << L'\u2550';
			}
			if (i < N)
			{
				std::wcout << L'\u256C';
			}
		}
		std::wcout << L'\u2563' << '\n' << L'\u2551';
		std::wcout << std::left << std::setw(ALIGN_W) << std::setfill(L' ') << "a1s";
		std::wcout << L'\u2551';
	}
	for (int i = 0; i < N; i++)
	{
		if (autoui)
		{
			std::wcout << a1s[i];
			if (i < N - 1)
			{
				std::wcout << ' ';
			}
		}
		else
		{
			std::wcout << std::right << std::setw(ALIGN_W) << std::setfill(L' ') << a1s[i];
			std::wcout << L'\u2551';
		}
	}
	if (!autoui)
	{
		std::wcout << '\n' << L'\u255A';
		for (int i = 0; i < N+1; i++)
		{
			for (int j = 0; j < ALIGN_W; j++)
			{
				std::wcout << L'\u2550';
			}
			if (i < N)
			{
				std::wcout << L'\u2569';
			}
		}
		std::wcout << L'\u255D' << '\n';
	}

	for (auto elem : mn)
	{
		std::wcout << elem << '\n';
	}
	std::wcout << cnt << '\n' << idx << '\n';
	cnt = 0;
	for (int i = 0; i < N; i++)
	{
		if (a1[i] > 0)
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
	cnt = -1;
	for (int i = 0; i < N; i++)
	{
		if (a2[i] > 0)
		{
			for (int j = 0; i < cnt; i++)
			{
				std::wcout << "0 ";
			}
			if (cnt == -1)
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
	for (int i = 0; i < N; i++)
	{
		if (a2[i] < 0)
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
	cnt = -1;
	for (int i = 0; i < N; i++)
	{
		if (a1[i] < 0)
		{
			for (int j = 0; i < cnt; i++)
			{
				std::wcout << "0 ";
			}
			if (cnt == -1)
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