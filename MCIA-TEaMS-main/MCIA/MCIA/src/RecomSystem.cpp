//
// Created by sorana on 1/11/2023.
//
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "../include/RecomSystem.h"

const char* RecomSystem::RecomLogParser::k_pathToLogFile = "../../../../RecomSystem/logs/train_logs.txt";
RecomSystem* RecomSystem::m_recomSystem = nullptr;

std::vector<uint32_t> RecomSystem::GetRecommendedMovies(int userId, int batchSize, int numMoviesToRecommend) {

   std::vector<uint32_t> res;

    PyObject* result = PyObject_CallFunction(m_recomFunction, "iii", userId, batchSize, numMoviesToRecommend);
    PyErr_Print();
    if(PyList_Check(result)){
        // okay, it's a list
        for (Py_ssize_t i = 0; i < PyList_Size(result); ++i) {
            PyObjectWrapper next{PyList_GetItem(result, i)};
            double value = PyFloat_AsDouble(next);
            res.push_back(value);
        }
    }


    return res;
}

void RecomSystem::UpdateModelByUserReview(int userId, int movieId, float rating) {
    PyObjectWrapper result{PyObject_CallFunction(m_updateFunction, "iif", userId, movieId, rating)};
    
}

void RecomSystem::RetrainModel()
{
    std::system("cmd.exe /c ..\\..\\..\\..\\RecomSystem\\retrain.bat");
}

bool RecomSystem::HasToRetrain()
{
    return RecomLogParser::toHours(RecomLogParser::getTimeSinceLastTrain()) > 2.0;
}


void RecomSystem::InitOnlyRetrain()
{
    PyObject* retrainModuleName = PyUnicode_FromString(RETRAIN_MODULE_NAME);
    m_retrainModule.SetPyObj(PyImport_Import(retrainModuleName));
    PyObject* retrainModuleDict = PyModule_GetDict(m_retrainModule);
    m_retrainFunction.SetPyObj(PyDict_GetItemString(retrainModuleDict, RETRAIN_FUNCTION_NAME));
}


RecomSystem::RecomSystem(bool forTrain)
{
    Py_Initialize();

    //surpress tensorflow warnings:
    PyRun_SimpleString("import os");
    PyRun_SimpleString("os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'");
    if (forTrain) {
        InitOnlyRetrain();
        return;
    }
    PyObject* recomModuleName = PyUnicode_FromString(RECOM_MODULE_NAME);
    PyObject* updateModuleName = PyUnicode_FromString(UPDATE_MODULE_NAME);

    m_recomModule.SetPyObj(PyImport_Import(recomModuleName));
    PyErr_Print();
    m_updateModule.SetPyObj(PyImport_Import(updateModuleName));
    
    PyObject* recomModuleDict = PyModule_GetDict(m_recomModule);
    PyObject* updateModuleDict = PyModule_GetDict(m_updateModule);
    
    m_recomFunction.SetPyObj(PyDict_GetItemString(recomModuleDict, RECOM_FUNCTION_NAME));
    m_updateFunction.SetPyObj(PyDict_GetItemString(updateModuleDict, UPDATE_FUNCTION_NAME));
    
    if(!m_recomFunction || !m_updateFunction){
        std::cout<<"Function does not exist!";
    } 

    //Py_Finalize();
}

RecomSystem& RecomSystem::GetInstance(bool forTrain)
{
    if (m_recomSystem == nullptr)
        m_recomSystem = new RecomSystem(forTrain);
    return *m_recomSystem;
}

void RecomSystem::DestroyInstance()
{
    Py_FinalizeEx();
    delete m_recomSystem;
    m_recomSystem = nullptr;
}

RecomSystem::~RecomSystem() {
    delete[] RECOM_MODULE_NAME;
    delete[] RETRAIN_MODULE_NAME;
    delete[] UPDATE_MODULE_NAME;
    delete[] RECOM_FUNCTION_NAME;
    delete[] RETRAIN_FUNCTION_NAME;
    delete[] UPDATE_FUNCTION_NAME;
}
std::string RecomSystem::RecomLogParser::getLastTrainingDate(char line[])
{
    std::string posInDay; // %H:%M:%S
    std::string posInYear; // %Y-%m-%d

    std::string fullLine(line);
    size_t idxStartPosInDay = fullLine.find_last_of(' ');
    size_t milliseconds = fullLine.find_last_of('.');
    posInDay = fullLine.substr(idxStartPosInDay + 1, milliseconds - idxStartPosInDay - 1);
    size_t idxStartYear = (fullLine.substr(0, idxStartPosInDay)).find_last_of(' ');
    posInYear = fullLine.substr(idxStartYear + 1, idxStartPosInDay - idxStartYear);
    return posInYear + " " + posInDay;
}

int RecomSystem::RecomLogParser::getTimeSinceLastTrain()
{
    std::ifstream f(k_pathToLogFile);
    int timeSinceLastTrain = 0;

    std::tm now{}; // current time
    std::tm lastTrainTM{}; // last train time

    // get last line from log file
    char* buff = new char[200];
    char* lastLine = new char[205];

    while (f.getline(buff, 200)) {
        strcpy_s(lastLine, 200, buff);
    }

    // get last train time
    std::string lastTrainStr = getLastTrainingDate(lastLine);
    std::istringstream ss(lastTrainStr);
    ss >> std::get_time(&lastTrainTM, "%Y-%m-%d %H:%M:%S");

    // get current time
    std::time_t tNow = std::time(0);   // get time now
    now = *std::localtime(&tNow);

    // convert to time since epoch
    std::time_t lastTrainDate = std::mktime(&lastTrainTM);
    std::time_t nowTime = std::mktime(&now);

    // check conversion error
    if (lastTrainDate == -1 || nowTime == -1) {
        std::cout << "Error converting time"; //TODO: ADD EXCEPTION
    }
    else {
        timeSinceLastTrain = std::difftime(nowTime, lastTrainDate);
    }
    return timeSinceLastTrain;
}


double RecomSystem::RecomLogParser::toHours(int epochTime)
{
    return epochTime / 3600.0;
}
