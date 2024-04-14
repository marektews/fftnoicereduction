#include "FFTPlan.h"

/**
 * @brief FFTPlan::FFTPlan
 * @param parent
 */
FFTPlan::FFTPlan(QObject *parent) : QObject{parent}
{}

/**
 * @brief FFTPlan::~FFTPlan
 */
FFTPlan::~FFTPlan()
{
    if(m_plan) fftw_destroy_plan(m_plan);
}

/**
 * @brief FFTPlan::Create_R2C_1D
 * @param n
 * @param in
 * @param out
 * @param flags
 * @return
 */
bool FFTPlan::Create_R2C_1D(int n, FFTRealBuffer::Ptr in, FFTComplexBuffer::Ptr out, int flags)
{
    m_plan = fftw_plan_dft_r2c_1d(n, in->data(), out->data(), flags);
    return m_plan != nullptr;
}

/**
 * @brief FFTPlan::Create_C2R_1D
 * @param n
 * @param in
 * @param out
 * @param flags
 * @return
 */
bool FFTPlan::Create_C2R_1D(int n, FFTComplexBuffer::Ptr in, FFTRealBuffer::Ptr out, int flags)
{
    m_plan = fftw_plan_dft_c2r_1d(n, in->data(), out->data(), flags);
    return m_plan != nullptr;
}

/**
 * @brief FFTPlan::Execute
 */
void FFTPlan::Execute()
{
    fftw_execute(m_plan);
}
