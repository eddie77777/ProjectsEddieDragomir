//
// Created by sorana on 1/14/2023.
//

#ifndef MCIA_USERRECOMSERVICE_H
#define MCIA_USERRECOMSERVICE_H
#include <future>
#include <fstream>
#include <vector>
#include <sstream>

class UserRecomService {
public:
    UserRecomService(uint32_t userId);
    ~UserRecomService();

public:
    std::vector<uint32_t> GetRecommendedMovies();
    void StartPopulatingRecommendedMovies();
    void StartUpdatingMovie(const uint32_t movieId, const float rating);
    void RetrainModel();
    void SetCurrentUserId(const uint32_t& userId);
private:
    const uint16_t BATCH_SIZE = 100;
    const uint16_t NMB_RECOMMENDED_MOVIES = 30;

private:
    uint32_t m_currentUserId;

    std::future<std::vector<uint32_t>> m_recommendedMoviesFuture;
    std::vector<uint32_t> m_recommendedMovies;
    std::mutex m_mutexUpdateMovies;

    std::ofstream m_logOutput;
    std::ostringstream m_helperStream;

};


#endif //MCIA_USERRECOMSERVICE_H
