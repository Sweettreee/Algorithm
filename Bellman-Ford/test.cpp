#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long iMax = (long long)10000000000;

vector<vector<pair<long long, long long>>> vecNode;
vector<long long> vecCost;
vector<bool> vecVisit;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	long long iCase = 0;
	cin >> iCase;

	for (long long i = 0; i < iCase; ++i)
	{
		long long iNode = 0;
		long long iRoad = 0;
		long long iWorm = 0;

		bool bIsOk = false;

		cin >> iNode >> iRoad >> iWorm;

		vecNode.resize(iNode + 1);

		for (long long j = 0; j < iRoad + iWorm; ++j)
		{
			long long iInput[3] = { 0,0,0 };
			cin >> iInput[0] >> iInput[1] >> iInput[2];
			if (j >= iRoad)
			{
				iInput[2] *= -1;
				vecNode[iInput[0]].emplace_back(iInput[1], iInput[2]);
			}
			else
			{
				vecNode[iInput[0]].emplace_back(iInput[1], iInput[2]);
				vecNode[iInput[1]].emplace_back(iInput[0], iInput[2]);
			}
		}

		queue<long long> queueNext;
		
		for (long long j = 1; j <= iNode; ++j)
		{
			vecCost.resize(iNode + 1);
			vecVisit.resize(iNode + 1, false);
			queueNext.push(j);
			vecCost[j] = 0;
			vecVisit[j] = true;

			long long iCount = 0;

			while (queueNext.empty() == false)
			{
				long long iNow = queueNext.front();
				queueNext.pop();

				for (auto& iter : vecNode[iNow])
				{
					if ((vecVisit[iter.first] == false) || (vecCost[iter.first] > vecCost[iNow] + iter.second))
					{
						vecVisit[iter.first] = true;
						queueNext.push(iter.first);
						vecCost[iter.first] = vecCost[iNow] + iter.second;
					}
				}

				if (vecCost[j] < 0)
				{
					bIsOk = true;
					break;
				}

				if (++iCount > (iRoad*3 + iWorm))
				{
					break;
				}
			}

			while (queueNext.empty() == false)
				queueNext.pop();

			vecCost.clear();
			vecVisit.clear();

			if (bIsOk == true)
				break;
		}

		if (bIsOk == true)
			cout << "YES" << "\n";
		else 
			cout << "NO" << "\n";

		for (auto& iter : vecNode)
			iter.clear();

		vecNode.clear();
	}

	return 0;
}
