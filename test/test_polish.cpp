#include "polish.h"
#include <string>
#include <gtest.h>

TEST(Polish, can_get_priority)
{
    EXPECT_EQ(Polish::GetPriority('+'), 3);
    EXPECT_EQ(Polish::GetPriority('-'), 3);
    EXPECT_EQ(Polish::GetPriority('*'), 4);
    EXPECT_EQ(Polish::GetPriority('/'), 4);
    EXPECT_EQ(Polish::GetPriority(')'), 2);
    EXPECT_EQ(Polish::GetPriority('('), 1);
    EXPECT_EQ(Polish::GetPriority('y'), -1);
    EXPECT_EQ(Polish::GetPriority('8'), 0);
}

TEST(Polish, can_convert)
{
    EXPECT_EQ(Polish::Convert('5'), 5);
    EXPECT_EQ(Polish::GetPriority('u'), -1);
}

TEST(Polish, can_use_plus)
{
    double rez;
    string exp = "1+1";
    TQueue < char >polish = Polish::ToPolish(exp);
    rez = Polish::Calculate(polish);
    EXPECT_EQ(rez, 2);
}

TEST(Polish, can_use_minus)
{
    double rez;
    string exp = "1-5";
    TQueue < char >polish = Polish::ToPolish(exp);
    rez = Polish::Calculate(polish);
    EXPECT_EQ(rez, -4);
}

TEST(Polish, can_use_division)
{
    double rez;
    string exp = "8/4";
    TQueue < char >polish = Polish::ToPolish(exp);
    rez = Polish::Calculate(polish);
    EXPECT_EQ(rez, 2);
}

TEST(Polish, can_get_double_number)
{
    double rez;
    string exp = "9/2";
    TQueue < char >polish = Polish::ToPolish(exp);
    rez = Polish::Calculate(polish);
    EXPECT_EQ(rez, 4.5);
}

TEST(Polish, can_use_multiplication)
{
    double rez;
    string exp = "5*4";
    TQueue < char >polish = Polish::ToPolish(exp);
    rez = Polish::Calculate(polish);
    EXPECT_EQ(rez, 20);
}

TEST(Polish, can_use_brackets)
{
    double rez;
    string exp = "5*(1+5)-9";
    TQueue < char >polish = Polish::ToPolish(exp);
    rez = Polish::Calculate(polish);
    EXPECT_EQ(rez, 21);
}

TEST(Polish, thow_when_use_wrong_symbol)
{
    string exp = "1y+1";
    ASSERT_ANY_THROW(TQueue < char >polish = Polish::ToPolish(exp));
}
