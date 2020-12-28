int MAIN() {
    int X,Y,x1,y1,x2,y2,dx1,dy1,dx2,dy2,s, t;
    X = read();
    Y = read();
    x1 = read();
    y1 = read();
    x2 = read();
    y2 = read();
    dx1 = read();
    dy1 = read();
    dx2 = read();
    dy2 = read();
    s = read();
    for(t=0;t<s;t = t + 1)
    {
        x1 += dx1;
        y1 += dy1;
        x2 += dx2;
        y2 += dy2;
 
        if(x1==X || x1==1)
            dx1 = dx1 * -1;
        if(y1==Y || y1==1)
            dy1 = dy1 * -1;
        if(x2==X || x2==1)
            dx2 = dx2 * -1;
        if(y2==Y || y2==1)
            dy2 = dy2* -1;
 
        if(x1==x2 && y1==y2)
        {
            int tempx=dx1, tempy=dy1;
            dx1=dx2;
            dx2=tempx;
            dy1=dy2;
            dy2=tempy;
        }
    }
    write(x1);
    write("\n");
    write(y1);
    write("\n");
    write(x2);
    write("\n");
    write(y2);
    write("\n");
    return 0;
}