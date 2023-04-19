#pragma once
#pragma warning(disable : 4996)
#include <cstdint>
#include <string>

class MovieIntermediary
{
public:
	MovieIntermediary();
	MovieIntermediary(uint32_t id, const std::string& title, const std::string& genres);

	void SetId(uint32_t id);
	void SetTitle(const std::string& title);
	void SetGenre(const std::string& genres);

	uint32_t GetId() const;
	std::string GetTitle() const;
	std::string GetGenre() const;

private:
	uint32_t m_id;
	std::string m_title;
	std::string m_genre;
};