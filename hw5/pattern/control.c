int main() {
    int a, b;
    float c, d;
    a = 1;
    b = 0;
    if (a > b) {
        write("correct1\n");
    } else {
        write("wrong1\n");
    }
    if (a < b) {
        write("wrong2\n");
    } else {
        write("correct2\n");
    }
    if (a == b) {
        write("wrong3\n");
    } else {
        write("correct3\n");
    }
    if (a != b) {
        write("correct4\n");
    } else {
        write("wrong4\n");
    }

    c = 1.0;
    d = 0.0;
    if (c > d) {
        write("correct5\n");
    } else {
        write("wrong5\n");
    }
    if (c < d) {
        write("wrong6\n");
    } else {
        write("correct6\n");
    }
    if (c != d) {
        write("correct7\n");
    } else {
        write("wrong7\n");
    }

    if (a && b) {
        write("wrong8\n");
    }

    if (a || b) {
        write("correct9\n");
    }

    a = 0;
    while (a<10) {
        write("correct: ");
        write(a);
        write("\n");
        a = a+1;
    }
    if (a == 10) {
        write("correct\n");
    }

    return 0;
}
