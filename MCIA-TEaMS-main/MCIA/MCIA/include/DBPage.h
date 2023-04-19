#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "NamedAsciiChars.h"

template<class TEntity>
class DBPage {
public:
	DBPage();
	DBPage(const std::vector<TEntity>& res, int nPages, int nCurrPage);

	std::vector<TEntity> GetResults() const;
	int GetNmbPages() const;
	int GetNmbCurrentPage() const;
	bool IsPageEmpty() const;

	friend std::ostream& operator<<(std::ostream& out, const DBPage<TEntity>& page)
	{
		const int fieldWidth = 120;
		std::string displayed_paginator;
		if (page.GetNmbCurrentPage() != 0)
		{
			displayed_paginator = displayed_paginator + "[b] ";
			displayed_paginator.push_back(NamedAsciiChars::GUILLEMET_LEFT);
			displayed_paginator.push_back(' ');
		}

		displayed_paginator = displayed_paginator + "Page " + std::to_string(page.GetNmbCurrentPage() + 1);
		if (page.GetNmbPages() != DBPage<TEntity>::NMB_PAGES_VALUE_NOT_NUMBERED)
			displayed_paginator = displayed_paginator + "/" + std::to_string(page.GetNmbPages()) + " ";
		else displayed_paginator.push_back(' ');
		if (page.GetNmbCurrentPage() != page.GetNmbPages() - 1)
		{
			displayed_paginator.push_back(NamedAsciiChars::GUILLEMET_RIGHT);
			displayed_paginator += " [n] ";
		}

		size_t parted_size = (fieldWidth - displayed_paginator.size()) / 2;
		std::cout << std::setfill((char)NamedAsciiChars::WHITE_BLOCK) << std::setw(parted_size);
		std::cout << " " << displayed_paginator << " ";
		std::cout << std::setfill((char)NamedAsciiChars::WHITE_BLOCK) << std::setw(parted_size);
		std::cout << '\n';
		for (auto& elem : page.GetResults())
			out << elem << '\n';

		std::cout << std::setfill((char)NamedAsciiChars::WHITE_BLOCK) << std::setw(fieldWidth);
		out << '\n';
		return out;
	}

public:
	static const uint8_t NMB_PAGES_VALUE_NOT_NUMBERED = -1;
	static const uint8_t DEFAULT_ROWS_NUMBER_PER_PAGE = 10;
private:
	std::vector<TEntity> m_results;
	int m_nmbPages;
	int m_nmbCurrPage;

};


template<class TEntity>
inline DBPage<TEntity>::DBPage()
	: m_results()
	, m_nmbPages(0)
	, m_nmbCurrPage(0)
{
}

template<class TEntity>
DBPage<TEntity>::DBPage(const std::vector<TEntity>& res, int nPages, int nCurrPage)
	: m_results(res)
	, m_nmbPages(nPages)
	, m_nmbCurrPage(nCurrPage)
{
}


template<class TEntity>
std::vector<TEntity> DBPage<TEntity>::GetResults() const
{
	return m_results;
}

template<class TEntity>
int DBPage<TEntity>::GetNmbPages() const
{
	return m_nmbPages;
}

template<class TEntity>
int DBPage<TEntity>::GetNmbCurrentPage() const
{
	return m_nmbCurrPage;
}

template<class TEntity>
bool DBPage<TEntity>::IsPageEmpty() const
{
	return m_nmbPages == 0 && m_results.size() == 0;
}
