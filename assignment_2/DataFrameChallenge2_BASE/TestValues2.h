//
// Created by ing.conti on 13/11/22.
// TestValues.h

#ifndef DATAFRAME_TESTVALUES_H
#define DATAFRAME_TESTVALUES_H


// test case 2: different number or rows:

DataFrame df_1("A B C");
df_1.setColumn("A", Column("8,7,11,19,12,19,6,15,13,10"));
df_1.setColumn("B", Column("1,12,3,8,9,20,12,8,1,17,9,17,"));
df_1.setColumn("C", Column("18,9,15,19,20,20,11,3,2,9,4"));

DataFrame df_2("D E F G");
df_2.setColumn("D", Column("11,9,17,20,11,20,8,10,12,3,7"));
df_2.setColumn("E", Column("12,2,18,14,18,18,12,123,213,123,132,"));
df_2.setColumn("F", Column("4,1"));
df_2.setColumn("G", Column("14,9,8,14,11,20,7,17,11,2,12,1"));


// columns where we ask for JOIN:
std::string ON_MY_COL{"A"};
std::string ON_OTHER_COLUMN{"D"};


#endif //DATAFRAME_TESTVALUES_H
