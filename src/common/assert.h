/**
********************************************************************************
* @file     assert.h
* @author   M.Niaraki
* @date     07/21/2023
* @brief    Defines ASSERT macro
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __ASSERT_H
#define __ASSERT_H

#if defined(DEBUG) && !defined(_TEST_)
#define ASSERT(expression) \
    do                     \
    {                      \
        if (!(expression)) \
            __ASM("BKPT"); \
    } while (0)
#else
#define ASSERT(expression) ((void)(expression))
#endif

#endif /* __ASSERT_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
