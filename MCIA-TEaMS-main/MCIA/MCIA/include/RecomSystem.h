//
// Created by sorana on 1/11/2023.
//

#ifndef MCIA_RECOMSYSTEM_H
#define MCIA_RECOMSYSTEM_H
//#include <Python.h>
#include "../include/PyObjectWrapper.h"
#include <vector>
#include <unordered_map>
#include <cstdint>

class RecomSystem {
public:
    enum TYPE {
        RECOM,
        RETRAIN,
        UPDATE_VALUES
    };
    RecomSystem(bool forTrain = false);
    RecomSystem(RecomSystem&) = delete;

    static RecomSystem& GetInstance(bool forTrain = false);
    static void DestroyInstance();

    std::vector<uint32_t> GetRecommendedMovies(int userId, int batchSize, int numMoviesToRecommend);
    void UpdateModelByUserReview(int userId, int movieId, float rating);
    void RetrainModel();
    static bool HasToRetrain();
    ~RecomSystem();

private:
    void InitOnlyRetrain();

private:

    PyObjectWrapper m_recomModule; // the module
    PyObjectWrapper m_updateModule; // the module
    PyObjectWrapper m_retrainModule; // the module dictionary

    PyObjectWrapper m_recomFunction;
    PyObjectWrapper m_updateFunction;
    PyObjectWrapper m_retrainFunction;

private:
    
    class RecomLogParser {
    public:
        static std::string getLastTrainingDate(char line[]);
        static int getTimeSinceLastTrain();
        static double toHours(int epochTime);
    private:
        static const char* k_pathToLogFile;
    };


private:
    const char* RECOM_MODULE_NAME = "RecomSystemRatingBased_recom"; //TODO: naming ref
    const char* RETRAIN_MODULE_NAME = "RecomSystemRatingBased_retrain"; //TODO: naming ref
    const char* UPDATE_MODULE_NAME = "RecomSystemRatingBased_update"; //TODO: naming ref
    const char* RECOM_FUNCTION_NAME="recommend_movies";
    const char* RETRAIN_FUNCTION_NAME="retrain_last_values";
    const char* UPDATE_FUNCTION_NAME="train_for_user";

    const double NMB_MAX_HOURS_BETWEEN_TRAINS = 2.0;

    static RecomSystem* m_recomSystem;
};


#endif //MCIA_RECOMSYSTEM_H
