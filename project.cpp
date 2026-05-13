#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Each node represents either a file or a directory.
// The BST is ordered alphabetically by name.
struct Node {
    string name;
    string type;   // "file" or "dir"
    Node* left;
    Node* right;

    Node(string n, string t) {
        name = n;
        type = t;
        left = right = NULL;
    }
};

// ─────────────────────────────────────────────
//  INSERT  — place a new file/dir in the tree
// ─────────────────────────────────────────────
Node* insert(Node* root, string name, string type) {
    if (root == NULL)
        return new Node(name, type);

    if (name < root->name)
        root->left = insert(root->left, name, type);
    else if (name > root->name)
        root->right = insert(root->right, name, type);
    else
        cout << "  '" << name << "' already exists.\n";

    return root;
}

// ─────────────────────────────────────────────
//  SEARCH  — find a file/dir by exact name
// ─────────────────────────────────────────────
Node* search(Node* root, string name) {
    if (root == NULL || root->name == name)
        return root;

    if (name < root->name)
        return search(root->left, name);
    else
        return search(root->right, name);
}

// Helper: find the leftmost (smallest) node — used during deletion
Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// ─────────────────────────────────────────────
//  DELETE  — remove a file/dir from the tree
// ─────────────────────────────────────────────
Node* deleteNode(Node* root, string name) {
    if (root == NULL) {
        cout << "  '" << name << "' not found.\n";
        return NULL;
    }

    if (name < root->name) {
        root->left = deleteNode(root->left, name);
    } else if (name > root->name) {
        root->right = deleteNode(root->right, name);
    } else {
        // Found it — handle the three standard BST delete cases

        // Case 1: no left child → promote right child
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        // Case 2: no right child → promote left child
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // Case 3: two children → replace with in-order successor (smallest on right)
        Node* successor = findMin(root->right);
        root->name = successor->name;
        root->type = successor->type;
        root->right = deleteNode(root->right, successor->name);
    }
    return root;
}

// ─────────────────────────────────────────────
//  TRAVERSALS
// ─────────────────────────────────────────────

// In-order → gives alphabetical listing (most useful for a file manager)
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << "  [" << (root->type == "dir" ? "DIR " : "FILE") << "]  " << root->name << "\n";
    inorder(root->right);
}

// Pre-order → root before children (good for showing hierarchy top-down)
void preorder(Node* root) {
    if (root == NULL) return;
    cout << "  [" << (root->type == "dir" ? "DIR " : "FILE") << "]  " << root->name << "\n";
    preorder(root->left);
    preorder(root->right);
}

// Post-order → children before root (useful for safe recursive deletion)
void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << "  [" << (root->type == "dir" ? "DIR " : "FILE") << "]  " << root->name << "\n";
}

// ─────────────────────────────────────────────
//  MENU HELPERS
// ─────────────────────────────────────────────
void printMenu() {
    cout << "\n╔══════════════════════════════╗\n";
    cout << "║   BST Directory/File Manager ║\n";
    cout << "╠══════════════════════════════╣\n";
    cout << "║  1. Create file              ║\n";
    cout << "║  2. Create directory         ║\n";
    cout << "║  3. Delete file/dir          ║\n";
    cout << "║  4. Search                   ║\n";
    cout << "║  5. List (in-order)          ║\n";
    cout << "║  6. List (pre-order)         ║\n";
    cout << "║  7. List (post-order)        ║\n";
    cout << "║  8. Exit                     ║\n";
    cout << "╚══════════════════════════════╝\n";
    cout << "  Choice: ";
}

// ─────────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────────
int main() {
    Node* root = NULL;
    int choice;
    string name;

    // Seed the tree with a few entries so it's not empty on startup
    root = insert(root, "Documents",  "dir");
    root = insert(root, "Downloads",  "dir");
    root = insert(root, "notes.txt",  "file");
    root = insert(root, "photo.png",  "file");
    root = insert(root, "Music",      "dir");
    root = insert(root, "resume.pdf", "file");

    cout << "\nWelcome! Tree seeded with some sample entries.\n";

    while (true) {
        printMenu();
        cin >> choice;
        cin.ignore(); // clear the newline left in the buffer

        if (choice == 1) {
            cout << "  File name: ";
            getline(cin, name);
            root = insert(root, name, "file");
            cout << "  File '" << name << "' created.\n";

        } else if (choice == 2) {
            cout << "  Directory name: ";
            getline(cin, name);
            root = insert(root, name, "dir");
            cout << "  Directory '" << name << "' created.\n";

        } else if (choice == 3) {
            cout << "  Name to delete: ";
            getline(cin, name);
            root = deleteNode(root, name);
            // deleteNode() already prints "not found" if missing,
            // so we only confirm success if the tree is intact
            if (root != NULL)
                cout << "  Deleted (if it existed).\n";

        } else if (choice == 4) {
            cout << "  Name to search: ";
            getline(cin, name);
            Node* found = search(root, name);
            if (found)
                cout << "  Found → [" << (found->type == "dir" ? "DIR " : "FILE") << "]  " << found->name << "\n";
            else
                cout << "  '" << name << "' not found.\n";

        } else if (choice == 5) {
            cout << "\n  In-order (alphabetical):\n";
            if (root == NULL) cout << "  (empty)\n";
            else inorder(root);

        } else if (choice == 6) {
            cout << "\n  Pre-order (root first):\n";
            if (root == NULL) cout << "  (empty)\n";
            else preorder(root);

        } else if (choice == 7) {
            cout << "\n  Post-order (children first):\n";
            if (root == NULL) cout << "  (empty)\n";
            else postorder(root);

        } else if (choice == 8) {
            cout << "\n  Bye!\n";
            break;

        } else {
            cout << "  Invalid option, try again.\n";
        }
    }

    return 0;
}