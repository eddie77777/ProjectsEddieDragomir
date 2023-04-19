//
// Created by sorana on 1/14/2023.
//
#include "../include/UserRecomService.h"
#include "../include/RecomSystem.h"
#include <iostream>


void UserRecomService::StartPopulatingRecommendedMovies() {
    auto getRecommendedMoviesTask = [&]() {
        
        std::lock_guard<std::mutex> lockGuard{ m_mutexUpdateMovies };
        //m_logOutput <<"started recom"<<std::this_thread::get_id()<<"\n";
        return RecomSystem::GetInstance().GetRecommendedMovies(m_currentUserId, BATCH_SIZE, NMB_RECOMMENDED_MOVIES);
    };
    m_recommendedMoviesFuture = std::async(std::launch::async, getRecommendedMoviesTask);
}


std::vector<uint32_t> UserRecomService::GetRecommendedMovies() {
    if (m_recommendedMovies.empty()) {
        m_recommendedMovies = m_recommendedMoviesFuture.get();
    }
    return m_recommendedMovies;
}

UserRecomService::UserRecomService(uint32_t userId) 
    : m_currentUserId(userId)
{
    /*m_logOutput.open(k_pathToLog);
    m_logOutput << "Logging started...\n";
    m_logOutput.close();*/
}

UserRecomService::~UserRecomService()
{
    m_logOutput.close();
}

void UserRecomService::StartUpdatingMovie(const uint32_t movieId, const float rating) {
    auto updateRecommendedMoviesTask = [=]() {
        
        std::lock_guard<std::mutex> lockGuard{m_mutexUpdateMovies};
        //std::cout << "starting to update " << std::this_thread::get_id() << "\n";
        RecomSystem::GetInstance().UpdateModelByUserReview(m_currentUserId, movieId, rating);
        //std::cout <<"finished update "<<std::this_thread::get_id()<<"\n";
        //m_logOutput.close();

    };
    std::thread updateThread{updateRecommendedMoviesTask};
    updateThread.detach();

    if (RecomSystem::HasToRetrain())
        RetrainModel();
}

void UserRecomService::RetrainModel()
{
    auto retrainModel = [&]() {
        std::lock_guard<std::mutex> lockGuard{ m_mutexUpdateMovies };
        //std::cout << "starting to retrain " << std::this_thread::get_id() << "\n";
        /*m_logOutput.open(k_pathToLog);
        m_logOutput << "starting to retrain " << std::this_thread::get_id() << "\n";
        m_logOutput << "done initializing on thread " << std::this_thread::get_id()<<"\n";*/
        // in the case the first check was performed while the retraining thread was running
        if (RecomSystem::HasToRetrain())
            RecomSystem::GetInstance().RetrainModel();
        //std::cout << "ended to retrain " << std::this_thread::get_id() << "\n";
        /*m_logOutput << "finished retraining " << std::this_thread::get_id() << "\n";
        m_logOutput.close();*/
    };
    std::thread retrainThread{ retrainModel };
    retrainThread.detach();
}

void UserRecomService::SetCurrentUserId(const uint32_t& userId)
{
    m_currentUserId = userId;
}
