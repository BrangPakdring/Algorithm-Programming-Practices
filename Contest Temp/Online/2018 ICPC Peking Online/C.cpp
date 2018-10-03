#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define speedup cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

string rankNumToStr[] = 
{
	"A",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"10",
	"J",
	"Q",
	"K"
};
set<string>rankLex;
map<string, ll>rankStrToNum;
ll challenger;
ll holder;
multiset<string>card[4];
bool challenged;
bool lie;
struct State
{
	ll rank, number;
}state;
multiset<ll>pileNum;

bool ReadCards()
{
	string line;
	holder = 0;
	while (getline(cin, line))
	{
		stringstream sstr(line);
		string str;
		card[holder].clear();
		while (sstr >> str)
		{
			card[holder].insert(str);
		}
		if (++holder == 4)break;
	}
	return !!holder;
}

bool IsGameOver()
{
	for (auto&st : card)
	{
		if (st.empty())return true;
	}
	return false;
}

bool IsRoundOver()
{
	return challenged;
}

void GiveCardsTo(ll player)
{
	for (auto&c : pileNum)
	{
		card[player].insert(rankNumToStr[c]);
	}
	pileNum.clear();
}

void Reveal()
{
	if (lie)GiveCardsTo(holder);
	else GiveCardsTo(challenger);
}

void SetLie()
{
	lie = true;
}

void SetPutDownNumber(ll number)
{
	state.number = number;
}

bool PutDownRequiedRank(ll rank, ll number)
{
	if (number == 0)return false;
	string rankStr = rankNumToStr[rank];
	if (card[holder].count(rankStr) < number)return false;
	for (ll i = 0; i < number; ++i)
	{
		pileNum.insert(rank);
		card[holder].erase(card[holder].find(rankStr));
	}
	return true;
}

void PutDownLexRankOne()
{
	assert(!card[holder].empty());
	ll rank = rankStrToNum[*card[holder].begin()];
	PutDownRequiedRank(rank, 1);
}

void Player0Hold()
{
	SetPutDownNumber(1);
	if (!PutDownRequiedRank(state.rank, 1))
	{
		SetLie();
		PutDownLexRankOne();
	}
}

void Player1Hold()
{
	ll cnt = card[1].count(rankNumToStr[state.rank]);
	SetPutDownNumber(cnt);
	if (!PutDownRequiedRank(state.rank, cnt))
	{
		SetLie();
		PutDownLexRankOne();
		SetPutDownNumber(1);
	}
}

void Player2Hold()
{
	ll cnt = card[2].count(rankNumToStr[state.rank]);
	SetPutDownNumber(cnt);
	if (!PutDownRequiedRank(state.rank, cnt))
	{
		SetLie();
		string choose;
		ll times = INT64_MAX;
		for (auto it = card[2].begin(); it != card[2].end(); it = card[2].upper_bound(*it))
		{
			if (times > card[2].count(*it))
			{
				times = card[2].count(*it);
				choose = *it;
			}
		}
		PutDownRequiedRank(rankStrToNum[choose], times);
		SetPutDownNumber(times);
	}
}

void Player3Hold()
{
	ll cnt = card[3].count(rankNumToStr[state.rank]);
	SetPutDownNumber(cnt);
	PutDownRequiedRank(state.rank, cnt);
	if (cnt < 3)
	{
		SetLie();
		if (card[3].empty());
		else
		{
			PutDownLexRankOne();
			SetPutDownNumber(cnt + 1);
		}
	}
}

void PlayerHold()
{
	switch (holder)
	{
		case 0: Player0Hold(); break;
		case 1: Player1Hold(); break;
		case 2: Player2Hold(); break;
		case 3: Player3Hold(); break;
	}
}

bool IsTheNextRoundHolder()
{
	return (holder + 1) % 4 == challenger;
}

bool HasToLieInTheNextRound()
{
	return card[challenger].count(rankNumToStr[(state.rank + 1) % 13]) == 0;
}

void SetChallenged()
{
	challenged = true;
}

void Player0Challenge()
{
	bool canChallenge = false;
	if (IsTheNextRoundHolder() && HasToLieInTheNextRound())
		canChallenge = true;
	else
	{
		ll p = state.number;
		ll q = card[0].count(rankNumToStr[state.rank]);
		if (p + q > 4)canChallenge = true;
	}
	if (!canChallenge)return;
	SetChallenged();
}

void Player1Challenge()
{
	bool canChallenge = false;
	if (IsTheNextRoundHolder() && HasToLieInTheNextRound())
		canChallenge = true;
	if (!canChallenge)return;
	SetChallenged();
}

void Player2Challenge()
{
	bool canChallenge = false;
	if (card[2].count(rankNumToStr[state.rank]) == 4)
		canChallenge = true;
	if (!canChallenge)return;
	SetChallenged();
}

void Player3Challenge()
{
	bool canChallenge = false;
	if (card[holder].empty())
		canChallenge = true;
	if (!canChallenge)return;
	SetChallenged();
}

void PlayerChallenge()
{
	switch (challenger)
	{
		case 0: Player0Challenge(); break;
		case 1: Player1Challenge(); break;
		case 2: Player2Challenge(); break;
		case 3: Player3Challenge(); break;
	}
	if (challenged)Reveal();
}

void InitNewRound()
{
	challenged = false;
	lie = false;	
}

void RunGame()
{
	for (holder = 0; 
		!IsGameOver(); 
		++holder %= 4, ++state.rank %= 13)
	{
		InitNewRound();
		PlayerHold();
		for (challenger = (holder + 1) % 4; 
			!IsRoundOver() && challenger != holder; 
			++challenger %= 4)
		{
			PlayerChallenge();
		}
	}
}

void InitGame()
{
	state.rank = 0;
	pileNum.clear();
}

void StartGame()
{
	InitGame();
	RunGame();
}

void InitLexicographic()
{
	for (auto&str : rankNumToStr)
	{
		rankLex.insert(str);
	}
}

void InitRankStrToNum()
{
	for (ll i = 0; i < 13; ++i)
	{
		rankStrToNum[rankNumToStr[i]] = i;
	}
}

void Init()
{
	InitLexicographic();
	InitRankStrToNum();
}

void PrintFinal()
{
	for (ll i = 0; i < 4; ++i)
	{
		bool first = true;
		if (card[i].empty())cout << "WINNER" << endl;
		else
		{
			multiset<ll>ansRanks;
			for (auto&c : card[i])
			{
				ansRanks.insert(rankStrToNum[c]);
			}
			for (auto&c : ansRanks)
			{
				if (!first)cout << ' ';
				first = false;
				cout << rankNumToStr[c];
			}
			cout << endl;
		}
	}
}

int main(int argc, char const *argv[])
{
	speedup;
	Init();
	while (ReadCards())
	{
		StartGame();
		PrintFinal();
	}
	return 0;
}
