class Program
    {
        static void Main(string[] args)
        {
 
        }
        private static string CheckWin(Player playerA, Player playerB)
        {
            return playerA.GetPlayerCard() > playerB.GetPlayerCard() ? playerA.Name : playerB.Name;
        }
        private static void CompareCards(Player playerA, Player playerB)
        {
            if (playerA.GetPlayerCard() > playerB.GetPlayerCard())
            {
                playerA.AddPoint();
            }
            else if (playerB.GetPlayerCard() > playerA.GetPlayerCard())
            {
                playerB.AddPoint();
            }
else Console.WriteLine("Ничья!");
        }
        private static List<int> GetListOfCards(int countOfCards)
        {
            List<int> ListOfCards = new List<int>();
            for(int i = 1; i <= countOfCards; i++)
            {
                ListOfCards.Add(i);
            }
            return ListOfCards;
        }
        private static void Shuffle(List<int> cardsList)
        {
            Random rnd = new Random();
            for (int i = cardsList.Count - 1; i > 0; i--)
            {
                int r = rnd.Next(i + 1);
                int temp = cardsList[r];
                cardsList[r] = cardsList[i];
                cardsList[i] = temp;
            }
        }
        private static Stack<int> ListToStack(List<int> cardsList)
        {
            return new Stack<int>(cardsList);
        }
    }
    class Player
    {
        public int Points;
        public string Name;
        private int _currentCard;
        public void TakeCard(Stack<int> cardsDeck)
        {
            _currentCard = cardsDeck.Pop();
        }
        public int GetPlayerCard()
        {
            return _currentCard;
        }
        public void AddPoint()
        {
            Points++;
        }
    }
