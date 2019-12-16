using System;

namespace Restaurant
{
    using System;

    class Program
    {
        static Random random = new Random();
        static void Main(string[] args)
        {
            Cafe cafe = new Cafe(2, 2);

            Console.WriteLine("Нажмите на Enter для начала игры и продолжайте нажимать, \nесли вы захотите увидеть нового посетителя в своем кафе. \n Для выхода из игры нажмите Escape\n");

            ConsoleKey key = Console.ReadKey(true).Key;

            while (true)
            {
                Person person = new Person(GenerateName(5), random.Next(15, 61), (PersonBehaviour)random.Next(0, 3));
                cafe.NewVisitor(person);
                Console.WriteLine(CountNullElements(cafe.Employees));

                //System.Threading.Thread.Sleep(2000);
                Console.WriteLine();
                key = Console.ReadKey(true).Key;
            }
        }

        static int CountNullElements(Employee[] array)
        {
            int count = 0;
            foreach (Employee emp in array)
            {
                if (emp == null)
                {
                    count++;
                }
            }

            return count;
        }

        static string GenerateName(int length)
        {
            Random rnd = new Random();
            string name = "";
            string vowels = "аеёиоуыэюя";
            string consonants = "бвгджзйклмнпрстфхцчшщ";
            name += consonants[rnd.Next(21)];
            name = name.ToUpper();
            for (int i = 0; i < length; i++)
            {
                name += (i % 2 == 0) ? vowels[rnd.Next(10)] : consonants[rnd.Next(21)];
            }
            return name;
        }
    }

    class Person
    {
        public string Name;
        public int Age;
        private PersonBehaviour Behaviour;
        public Person(string name, int age, PersonBehaviour behaviour)
        {
            Name = name;
            Age = age;
            Behaviour = behaviour;
        }
        public Person(string name, int age)
        {
            Name = name;
            Age = age;
        }

        public PersonBehaviour GetBehaviour()
        {
            return Behaviour;
        }
    }
    class Employee : Person
    {
        protected int Salary;
        public Employee(string name, int age, int salary) : base(name, age)
        {
            Salary = salary;
        }
        public int GetSalary()
        {
            return Salary;
        }
    }
    class Waiter : Employee
    {
        public Waiter(string name, int age, int salary) : base(name, age, salary)
        {
        }
    }
    class Security : Employee
    {
        public Security(string name, int age, int salary) : base(name, age, salary)
        {
        }
    }
    class Cafe
    {
        public int CurrentWaiters = 0;
        public int CurrentSecurities = 0;
        public int MaxWaiters;
        public int MaxSecurities;
        public Employee[] Employees;
        public Cafe(int maxWaiters, int maxSecurities)
        {
            MaxWaiters = maxWaiters;
            MaxSecurities = maxSecurities;
            Employees = new Employee[MaxSecurities + MaxWaiters];
        }
        public void RecruitmentSecurity(Person candidate)
        {
            if (CurrentSecurities < MaxSecurities)
            {
                Employees[CurrentSecurities] = new Security(candidate.Name, candidate.Age, 27845);
                Console.WriteLine("Поздравляем, {0}! \nВы приняты на должность охранника с зарплатой {1} рублей!", Employees[CurrentSecurities].Name, Employees[CurrentSecurities].GetSalary());
                CurrentSecurities++;
            }
            else Console.WriteLine("Охрана!!! Вышвырнуть {0} из зала!", candidate.Name);
        }
        public void RecruitmentWaiter(Person candidate)
        {
            if (CurrentWaiters < MaxWaiters)
            {
                Employees[MaxSecurities + CurrentWaiters] = new Waiter(candidate.Name, candidate.Age, 99990);
                Console.WriteLine("{0}, без Вас мы не справимся! \nВы приняты на должность официанта с зарплатой {1} рублей!", Employees[MaxSecurities + CurrentWaiters].Name, Employees[MaxSecurities + CurrentWaiters].GetSalary());
                CurrentWaiters++;
            }
            else Console.WriteLine("Ох... очень жаль, {0}, \nно у нас сейчас нет места для ещё одного официанта :(", candidate.Name);
        }
        public void NewVisitor(Person alien)
        {
            switch (alien.GetBehaviour())
            {
                case PersonBehaviour.Agressive:
                    Console.WriteLine("Пожалуйста поспокойнее, {0}!", alien.Name);
                    RecruitmentSecurity(alien);
                    break;
                case PersonBehaviour.Passive:
                    Console.WriteLine("С вас 30000 рублей, уважаемый {0}!", alien.Name);
                    break;
                case PersonBehaviour.Polite:
                    Console.WriteLine("О, Вы так вежливы, {0}! \nВозможно у меня будет для Вас кое-какое предложение!", alien.Name);
                    RecruitmentWaiter(alien);
                    break;
            }
        }
    }
    enum PersonBehaviour
    {
        Agressive,
        Passive,
        Polite
    }
}
