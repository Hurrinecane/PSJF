#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class Processor
{
private:
	struct Process
	{
		Process()
		{
			time = 0;
			enter_time = 0;
			running_time = 0;
		};

		Process(int time_, int enter_time_)
		{
			time = time_;
			enter_time = enter_time_;
			running_time = 0;
		};
		int time;
		int running_time;
		int enter_time;
	};

	int numberOfProcesses = 0;
	int mas_length = 4;

	Process* process_mas = new Process[mas_length];

private:
	Process* resize(Process* process_mas, int OldSize, int NewSize)
	{
		if (OldSize > NewSize)
			return process_mas;
		Process* new_process_mas = new Process[NewSize];
		memcpy(new_process_mas, process_mas, sizeof(Process) * OldSize);
		delete[] process_mas;
		return new_process_mas;
	}

public:
	void AddProcess()
	{
		int time, enter_time;
		cout << "������� � " << numberOfProcesses + 1 << endl;
		do
		{
			cout << "������� ����� ���������� ��������: ";
			cin >> time;

			if (time < 1) cout << "������������ ����� ���������� ��������!" << endl;
		} while (time < 1);

		if (numberOfProcesses > 0)
			do
			{
				cout << "������� ����� ���������: ";
				cin >> enter_time;
				if (enter_time <= process_mas[numberOfProcesses - 1].enter_time) cout << "������������ ����� ��������� ��������!" << endl;
			} while (enter_time <= process_mas[numberOfProcesses - 1].enter_time);
		else
			enter_time = 0;

		numberOfProcesses++;

		if (numberOfProcesses > mas_length)
		{
			process_mas = resize(process_mas, mas_length, numberOfProcesses);
			mas_length++;
		}
		process_mas[numberOfProcesses - 1].time = time;
		process_mas[numberOfProcesses - 1].enter_time = enter_time;
	};

	void PlanPSJF()
	{
		int total_time = 0;
		for (int i = 0; i < numberOfProcesses; i++)
			total_time += process_mas[i].time;

		int** processor_time = new int* [mas_length];
		for (int i = 0; i < mas_length; i++)
		{
			processor_time[i] = new int[total_time];
			for (int j = 0; j < total_time; j++)
				processor_time[i][j] = -1;
		}

		int run_process = 0;

		for (int j = 0; j < total_time; j++)
		{
			run_process = 0;
			for (int i = 0; i < numberOfProcesses; i++)
			{
				if (j >= process_mas[i].enter_time && process_mas[i].running_time < process_mas[i].time)	//���� ������� ��������� � ��� �� ����������
					if (process_mas[run_process].running_time == process_mas[run_process].time || process_mas[i].time - process_mas[i].running_time < process_mas[run_process].time - process_mas[run_process].running_time)
					{
						processor_time[run_process][j] = 0;
						run_process = i;
					}
					else processor_time[i][j] = 0;
			}
			processor_time[run_process][j] = 1;
			process_mas[run_process].running_time++;
		}

		cout << endl
			<< "PSJF"
			<< endl
			<< "======================================================================================================================"
			<< endl
			<< "Process  	time	enter time" << "	";

		for (int i = 1; i <= total_time; i++)
			cout << i << " ";
		cout << endl;

		for (int i = 0; i < numberOfProcesses; i++)
		{
			cout << "Process " << i + 1 << "	" << process_mas[i].time << "	" << process_mas[i].enter_time << "		";
			int run_time = 0;
			for (int j = 0; j < total_time; j++)
			{
				if (processor_time[i][j] == 1)
				{
					cout << "* ";
					run_time++;
					if (int(log10(j + 1) + 1) == 2)
						cout << " ";
				}
				else if (processor_time[i][j] == 0)
				{
					cout << "# ";
					if (int(log10(j + 1) + 1) == 2)
						cout << " ";
				}
				else if (processor_time[i][j] == -1)
				{
					cout << "  ";
					if (int(log10(j + 1) + 1) == 2)
						cout << " ";
				}
				if (run_time == process_mas[i].time || j == total_time - 1)
				{
					cout << endl;
					break;
				}
			}
		}
		cout << "======================================================================================================================" << endl;
		for (int i = 0; i < mas_length - 1; i++)
			delete[] processor_time[i];
	}
};

int main()
{
	setlocale(0, "");
	Processor CPU;
	CPU.AddProcess();
	CPU.AddProcess();
	CPU.AddProcess();
	system("cls");
	CPU.PlanPSJF();
	system("pause");
}
/*

8 5 2 2 4

10 4 3 8 5 5 6

*/