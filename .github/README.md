<h1 align="center">
  ZAPPY-SERVER - 2025<br>
  <img src="https://raw.githubusercontent.com/catppuccin/catppuccin/main/assets/palette/macchiato.png" width="600px" alt="color palette"/>
  <br>
</h1>

<p align="center">
  Server for zappy project<br>
</p>

---

## Usage

Clone the repository

```bash
git clone --recurse-submodules git@github.com:mbarleon/Zappy-Server.git
```

Build the project

```bash
./build.sh
```

When exiting the server (by pressing CTRL+C), the SIGINT will be caught to exit
gracefully. If you press CTRL+C 3 times, the server will forcefully exit by
calling abort(3). This will cause memory leaks as nothing will be freed if this
happens.

---

## WARNING

Dear Epitech students, this server was developped in accordance with Epitech's C coding-style (as of 2025), as it was used in my own projects. However, using it directly in your projects may result in a grade penalty (e.g., -42). Use it with caution, and do not add it to your repository unless you have explicit approval from your local pedagogical staff.
