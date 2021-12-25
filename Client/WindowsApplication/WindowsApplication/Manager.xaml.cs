using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;


namespace WindowsApplication
{
    /// <summary>
    /// Interaction logic for Manager.xaml
    /// </summary>
    public partial class Manager : Window
    {
        ObservableCollection<User> users = new ObservableCollection<User>();
        public Manager(string username)
        {
            InitializeComponent();
            Friend.load(username);
            for (int i = 0; i < Friend.Friends.Count; i++)
            {
                users.Add(new User() { Name = Friend.Friends[i].Nickname, UserName = Friend.Friends[i].Username });
                Console.WriteLine(Friend.Friends[i].Nickname);
            }
            listView.ItemsSource = users;
        }
        private void listView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
    }
}
