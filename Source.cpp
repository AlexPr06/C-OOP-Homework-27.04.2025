#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

#define INDENT std::cout << endl;

/*
 Клас Product (Товар)
Призначення: представляє окремий товар у магазині.
Поля (атрибути):
назва (string)
опис (string)
ціна (float)
кількість_в_наявності (int)
Методи:
змінити_ціну(нова_ціна)
зменшити_кількість(кількість)
збільшити_кількість(кількість)
 */

using namespace std;

class Product {
public:
    string name;
    string description;
    float price;
    int stock;

    Product(string name, string description, float price, int stock)
        : name(name), description(description), price(price), stock(stock) {
    }

    void changePrice(float newPrice) {
        price = newPrice;
    }

    void decreaseStock(int quantity) {
        if (stock >= quantity) {
            stock -= quantity;
        }
        else {
            cout << "Not enough stock!" << endl;
        }
    }

    void increaseStock(int quantity) {
        stock += quantity;
    }

    ~Product() {}
};

/*
 Клас Cart (Кошик)
Призначення: тимчасове зберігання товарів, які користувач хоче купити.
Поля:
товари (список пар: товар + кількість)
Методи:
додати_товар(продукт, кількість)
видалити_товар(продукт)
порахувати_суму()
очистити_кошик()

*/


class Cart {
public:
    vector<pair<Product*, int>> items;

    void addProduct(Product* product, int quantity) {
        items.push_back({ product, quantity });
    }

    void removeProduct(Product* product) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->first == product) {
                items.erase(it);
                break;
            }
        }
    }

    float calculateTotal() {
        float total = 0.0;
        for (auto& pair : items) {
            total += pair.first->price * pair.second;
        }
        return total;
    }

    void clearCart() {
        items.clear();
    }

    ~Cart() {}
};


/*
 Клас Order (Замовлення)
Призначення: підтверджене замовлення користувача.
Поля:
ідентифікатор_замовлення (int або string)
список_товарів (список пар: товар + кількість)
загальна_сума (float)
статус (string: "в обробці", "доставляється", "виконано")
Методи:
змінити_статус(новий_статус)
показати_інформацію_про_замовлення()
 */
class Order {
public:
    string orderId;
    vector<pair<Product*, int>> productList;
    float totalAmount;
    string status;

    Order(string id, vector<pair<Product*, int>> products, float total)
        : orderId(id), productList(products), totalAmount(total), status("processing") {
    }

    void changeStatus(string newStatus) {
        status = newStatus;
    }

    void showOrderInfo() {
        cout << "Order #" << orderId << endl;
        for (auto& pair : productList) {
            cout << pair.first->name << " - " << pair.second << " pcs" << endl;
        }
        cout << fixed << setprecision(2);
        cout << "Total: $" << totalAmount << endl;
        cout << "Status: " << status << endl;
    }
};

/*
 Клас User (Користувач)
Призначення: представляє клієнта інтернет-магазину.
Поля:
ім’я (string)
email (string)
кошик (Cart)
історія_замовлень (список Order)
Методи:
додати_в_кошик(продукт, кількість)
оформити_замовлення()
переглянути_замовлення()
 */

class User {
public:
    string name;
    string email;
    Cart cart;
    vector<Order> orderHistory;

    User(string name, string email) : name(name), email(email) {}

    void addToCart(Product* product, int quantity) {
        cart.addProduct(product, quantity);
    }

    void placeOrder() {
        float total = cart.calculateTotal();
        string id = to_string(rand() % 1000000);
        Order newOrder(id, cart.items, total);
        orderHistory.push_back(newOrder);
        cart.clearCart();
        cout << "Order placed!" << endl;
    }

    void viewOrders() {
        for (auto& order : orderHistory) {
            order.showOrderInfo();
            cout << "-----------------------------" << endl;
        }
    }
};

void showProducts(vector<Product>& products) {
    cout << "\nAvailable Products:\n";
    for (size_t i = 0; i < products.size(); ++i) {
        cout << i + 1 << ") " << products[i].name << " - $" << products[i].price
            << " (" << products[i].stock << " in stock)\n";
    }
}

void showCart(User& user) {
    cout << "\nYour Cart:\n";
    for (auto& item : user.cart.items) {
        cout << "- " << item.first->name << ": " << item.second
            << " x $" << item.first->price << "\n";
    }
    cout << "Total: $" << fixed << setprecision(2) << user.cart.calculateTotal() << endl;
}


int main() {
    system("chcp 65001 > nul");
	srand(time(0)); 

    vector<Product> storeProducts = {
        Product("Laptop", "Gaming laptop", 1200.0f, 5),
        Product("Phone", "Smartphone with 128GB", 600.0f, 10),
        Product("Headphones", "Noise-cancelling", 150.0f, 7)
    };

    User user("John Doe", "john@example.com");

    int choice;
    while (true) {
        cout << "\n--- Online Store ---\n";
        cout << "1. Show products\n";
        cout << "2. Add product to cart\n";
        cout << "3. View cart\n";
        cout << "4. Place order\n";
        cout << "5. View order history\n";
        cout << "6. Exit\n";
        INDENT

        while (true)
        {
            cout << "Your choice: ";
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED << "Invalid input. Please enter a number!\n" << RESET;
                continue;
            }
        	break;
        }
        

        if (choice == 1) {
            showProducts(storeProducts);

        }
        else if (choice == 2) {
            showProducts(storeProducts);
            int prodIndex, quantity;
            while (true)
            {
                cout << "Select product number: ";
                cin >> prodIndex;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << RED << "Invalid input. Please enter a number!\n" << RESET;
					continue;
				}
				if (prodIndex < 1 || prodIndex > storeProducts.size()) {
					cout << RED << "Invalid product number!\n" << RESET;
					continue;
				}
				break;
            }
            while (true)
            {
                cout << "Enter quantity: ";
                cin >> quantity;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << RED << "Invalid input. Please enter a number!\n" << RESET;
                    continue;
                }
				if (quantity <= 0) {
					cout << RED << "Quantity must be greater than 0!\n" << RESET;
					continue;
				}
				break;
            }
          

            if (prodIndex >= 1 && prodIndex <= storeProducts.size()) {
                Product& selected = storeProducts[prodIndex - 1];
                if (selected.stock >= quantity) {
                    selected.decreaseStock(quantity);
                    user.addToCart(&selected, quantity);
                    cout << "Added to cart!\n";
                }
                else {
                    cout << "Not enough in stock!\n";
                }
            }
            else {
                cout << "Invalid product!\n";
            }

        }
        else if (choice == 3) {
            showCart(user);

        }
        else if (choice == 4) {
            if (user.cart.items.empty()) {
                cout << "Cart is empty!\n";
            }
            else {
                user.placeOrder();
            }

        }
        else if (choice == 5) {
			if (user.orderHistory.empty()) {
				cout << "No orders found!\n";
			}
			else {
				user.viewOrders();
			}
        }
        else if (choice == 6) {
            cout << "Thanks for shopping!\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
