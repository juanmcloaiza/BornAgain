#ifndef OMPISIMULATION_H
#define OMPISIMULATION_H


class Simulation;

class OMPISimulation
{
public:

    void runSimulation(const Simulation *simulation);

private:
    Simulation *m_simulation;
};


#endif

