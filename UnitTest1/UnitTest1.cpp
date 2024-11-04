#include "pch.h"
#include "CppUnitTest.h"
#include "..\PDS_9\Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestReadGraphFromFile)
		{
			{
				std::ofstream outFile("test_graph.txt");
				outFile << "1 2 3\n2 1 4 5\n3 1 6\n4 2\n5 2\n6 3\n";
				outFile.close();

				std::vector<std::vector<unsigned int>> graph;
				bool result = readGraphFromFile("test_graph.txt", graph);

				Assert::IsTrue(result, L"Функція повинна повернути true для коректного файлу.");
				Assert::AreEqual(static_cast<int>(6), static_cast<int>(graph.size()), L"Кількість вершин має бути 6.");

				Assert::AreEqual(static_cast<int>(3), static_cast<int>(graph[0].size()), L"Вершина 1 повинна мати 3 сусіди.");
				Assert::AreEqual((unsigned int)0, graph[0][0], L"Неправильний сусід для вершини 1.");
				Assert::AreEqual((unsigned int)1, graph[0][1], L"Неправильний сусід для вершини 1.");
				Assert::AreEqual((unsigned int)2, graph[0][2], L"Неправильний сусід для вершини 1.");
			}

			{
				std::vector<std::vector<unsigned int>> graph;
				bool result = readGraphFromFile("invalid_path.txt", graph);
				Assert::IsFalse(result, L"Функція повинна повернути false для невірного шляху.");
				Assert::AreEqual(static_cast<size_t>(0), graph.size(), L"Граф повинен бути пустим.");
			}
		}
	};
}
