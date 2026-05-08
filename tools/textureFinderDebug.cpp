#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {
    const char *imageFile;
    if (argc == 1) {
        imageFile = "assets/images/52571.png";
    } else {
        imageFile = argv[1];
    }
    const int screenWidth = 1100;
    const int screenHeight = 720; 
    InitWindow(screenWidth, screenHeight, "Sprite Tool - [S] Snap Toggle");

    Texture2D sprites = LoadTexture(imageFile);

    Camera2D camera = { 0 };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.zoom = 1.0f;

    Vector2 startPos = { 0 };
    bool isSelecting = false;
    bool snapToGrid = true; 

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // --- 1. Utility Controls ---
        if (IsKeyPressed(KEY_S)) snapToGrid = !snapToGrid;

        // --- 2. Camera Logic ---
        if (GetMouseWheelMove() != 0) {
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            camera.offset = GetMousePosition();
            camera.target = mouseWorldPos;
            camera.zoom += GetMouseWheelMove() * 0.1f;
            if (camera.zoom < 0.1f) camera.zoom = 0.1f;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 delta = GetMouseDelta();
            camera.target = Vector2Add(camera.target, Vector2Scale(delta, -1.0f / camera.zoom));
        }

        // --- 3. Coordinate Handling ---
        Vector2 worldMouse = GetScreenToWorld2D(GetMousePosition(), camera);
        
        if (snapToGrid) {
            worldMouse.x = roundf(worldMouse.x);
            worldMouse.y = roundf(worldMouse.y);
        }

        // --- 4. Selection Logic ---
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            startPos = worldMouse;
            isSelecting = true;
        }

        if (isSelecting && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isSelecting = false;
            
            // Calculate the true top-left corner and positive dimensions
            float rectX = (worldMouse.x < startPos.x) ? worldMouse.x : startPos.x;
            float rectY = (worldMouse.y < startPos.y) ? worldMouse.y : startPos.y;
            float width = (float)fabs(worldMouse.x - startPos.x);
            float height = (float)fabs(worldMouse.y - startPos.y);

            // Only print if there's an actual area selected
            if (width > 0 && height > 0) {
                printf("\n// --- New Sprite Selection ---\n");
                printf("Rectangle source = { %.0f.0f, %.0f.0f, %.0f.0f, %.0f.0f };\n", 
                        rectX, rectY, width, height);
                
                printf("Rectangle dest = { x, y, %.0f.0f, %.0f.0f }; // replace x, y\n", 
                        width, height);
                
                printf("DrawTexturePro(sprites, source, dest, (Vector2){ 0, 0 }, 0.0f, WHITE);\n");
                
                // Cleaned up the extra printf line for clarity
                printf("DrawTexturePro(sprites, (Rectangle){ %.0f.0f, %.0f.0f, %.0f.0f, %.0f.0f }, (Rectangle){ x, y, %.0f.0f, %.0f.0f }, (Vector2){ 0, 0 }, 0.0f, WHITE);\n", 
                        rectX, rectY, width, height, width, height);            
            }
        }

        // --- 5. Drawing ---
        BeginDrawing();
            ClearBackground(DARKGRAY);

            BeginMode2D(camera);
                DrawTexture(sprites, 0, 0, WHITE);

                if (isSelecting) {
                    float curW = worldMouse.x - startPos.x;
                    float curH = worldMouse.y - startPos.y;
                    Rectangle sel = { 
                        (curW < 0) ? worldMouse.x : startPos.x, 
                        (curH < 0) ? worldMouse.y : startPos.y, 
                        (float)fabs(curW), (float)fabs(curH) 
                    };
                    // Line thickness scales with zoom so it doesn't get "fat"
                    DrawRectangleLinesEx(sel, 2.0f / camera.zoom, RED);
                }
            EndMode2D();

            // --- UI Bar ---
            DrawRectangle(0, 0, screenWidth, 40, Fade(BLACK, 0.8f));
            DrawText("R-Click: Pan | Scroll: Zoom | L-Click: Select", 15, 12, 15, RAYWHITE);
            
            Color snapColor = snapToGrid ? GREEN : RED;
            DrawRectangleLines(500, 8, 120, 24, snapColor);
            DrawText(snapToGrid ? "SNAP: ON [S]" : "SNAP: OFF [S]", 510, 13, 15, snapColor);

            DrawText(TextFormat("X: %.0f Y: %.0f", worldMouse.x, worldMouse.y), 
                     screenWidth - 150, 12, 20, YELLOW);

        EndDrawing();
    }

    UnloadTexture(sprites);
    CloseWindow();
    return 0;
}
