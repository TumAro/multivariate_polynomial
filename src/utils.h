#pragma once
#include <iostream>
#include <string>
#include <vector>

void Log(std::string txt);
void lineEnd();

int max(int a, int b);
int min(int a, int b);

double pow(double base, int exp);
int factorial(int n);

std::vector<float> joinVectors(std::vector<float> vec1, std::vector<float> vec2);

std::vector<std::vector<int>> lexorderArray(int total, int remainder_pos, std::vector<int> indices = {}, int pos = 0);