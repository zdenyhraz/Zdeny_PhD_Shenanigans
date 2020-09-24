#pragma once
#include "Optimization.h"

class Evolution : public OptimizationAlgorithm
{
public:
  Evolution(int N, const std::string &optname = "default");
  OptimizationResult Optimize(ObjectiveFunction f) override;
  void SetFileOutput(const std::string &path);
  void SetPlotOutput(bool PlotOutput) { mPlotOutput = PlotOutput; };
  void SetParameterNames(const std::vector<std::string> &ParameterNames) { mParameterNames = ParameterNames; };
  void SetOptimizationName(const std::string &optname) { mOptimizationName = optname; }

  enum MutationStrategy
  {
    RAND1,
    BEST1,
    RAND2,
    BEST2
  };

  enum CrossoverStrategy
  {
    BIN,
    EXP
  };

  int mNP = 4;
  double mF = 0.65;
  double mCR = 0.95;
  MutationStrategy mMutStrat = RAND1;
  CrossoverStrategy mCrossStrat = BIN;

private:
  struct Entity
  {
    Entity();
    Entity(int N);

    std::vector<double> params;
    double fitness;
  };

  struct Offspring
  {
    Offspring();
    Offspring(int N, int nParents);
    void UpdateDistinctParents(int eid, int NP);
    void UpdateCrossoverParameters(CrossoverStrategy crossoverStrategy, double CR);

    std::vector<double> params;
    double fitness;
    std::vector<int> parentIndices;
    std::vector<bool> crossoverParameters;
  };

  struct Population
  {
    Population();
    bool Initialize(int NP, int N, ObjectiveFunction f, const std::vector<double> &LB, const std::vector<double> &UB, int nParents);
    void UpdateDistinctParents(int eid);
    void UpdateCrossoverParameters(int eid, CrossoverStrategy crossoverStrategy, double CR);
    void UpdateOffspring(int eid, MutationStrategy mutationStrategy, ObjectiveFunction f, double F, const std::vector<double> &LB, const std::vector<double> &UB);
    void PerformSelection();
    void UpdatePopulationFunctionEvaluations();
    void UpdateOffspringFunctionEvaluations();
    void UpdateBestEntity();
    void UpdateTerminationCriterions(double bestToAverageFitnessRatioThreshold);

    std::vector<Entity> entities;
    std::vector<Offspring> offspring;
    Entity bestEntity;
    int functionEvaluations;
    double averageFitness;
    double absoluteDifference;
    double relativeDifference;
    int relativeDifferenceGenerationsOverThreshold;

  private:
    void InitializePopulation(int NP, int N, ObjectiveFunction f, const std::vector<double> &LB, const std::vector<double> &UB);
    void InitializeBestEntity();
    void InitializeOffspring(int nParents);
  };

  bool CheckObjectiveFunctionNormality(ObjectiveFunction f);
  int GetNumberOfParents();
  bool InitializeOutputs();
  void UninitializeOutputs(const Population &population, TerminationReason reason);
  void UpdateOutputs(int generation, const Population &population);
  void CheckTerminationCriterions(const Population &population, int generation, bool &terminate, TerminationReason &reason);
  std::string GetOutputFileString(int generation, const std::vector<double> &bestEntity, double bestFitness);

  bool mFileOutput = false;
  bool mPlotOutput = true;
  double mINPm = 5.4;
  double mAbsoluteDifferenceThreshold = 1e-8;
  double mRelativeDifferenceThreshold = 0.75;
  int mRelativeDifferenceGenerationsOverThresholdThreshold = 10;
  std::string mOptimizationName;
  std::string mOutputFilePath;
  std::ofstream mOutputFile;
  std::vector<std::string> mParameterNames;
};
