int main() {
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ExpressionConverter converter;
    string expression;

    cout << "Абстрактная вычислительная машина\n";
    cout << "Введите постфиксное выражение: ";
    getline(cin, expression);

    try {
        converter.setExpression(expression);
        vector<string> instructions = converter.convert();
        printInstructions(instructions);
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
