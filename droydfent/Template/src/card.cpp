#include "card.h"

    Card::Card(string preset) {
        name = preset;
        unname = "un" + name;
        texture = LoadTexture((string(GetApplicationDirectory()).substr(0, string(GetApplicationDirectory()).size() - 4) + "assets/cards/" + name + ".png").c_str());
        target = D["cards"][name]["target"];
        type = D["cards"][name]["type"];
    }


    void Card::draw(int x, int y, int sz, bool selected) {
        //draw the texture2d
        Rectangle source = {0, 0, (float)(texture.width), (float)(texture.height)};
        Rectangle dest = {(float)x, (float)y, (float)(texture.width), (float)(texture.height)};
        Vector2 empty = {0, 0};

        if (selected) {
            DrawTexturePro(texture, source, dest, empty, 0, RED);
        } else {
            DrawTexturePro(texture, source, dest, empty, 0, WHITE);
        }

        //DrawTexture(texture, x, y, WHITE);
        //cout << "niga" << x << y << endl;
    }


