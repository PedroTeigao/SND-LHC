void acosag(){

    float valor = 7.9;

    while (valor > 1.0 || valor < -1.0) {
        if (valor > 1.0)
            valor -= 2.0;
        else if (valor < -1.0)
            valor += 2.0;
    }

    std::cout << "O valor final é: " << valor << std::endl;

}