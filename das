[33mcommit 9ac0add8b27c034fca304d9a41ff2a406263b6cd[m[33m ([m[1;36mHEAD[m[33m -> [m[1;32mmain[m[33m, [m[1;31morigin/main[m[33m)[m
Author: cevher kemal sirin <76917072+cevherkemalsirin@users.noreply.github.com>
Date:   Thu Mar 26 18:48:33 2026 +0200

    Seperate the engine code from game code
    
    Engine code consist of rendering, game loop and main function must keep
    hidden from the game. Seperate Game Project with seperate cmake needed.
    Now Gameapplication class can define Engine function GetApplication() to
    run the game.

[33mcommit a94b441eddfed71fa850f49db3e6a89be920b4cc[m
Author: cevher kemal sirin <76917072+cevherkemalsirin@users.noreply.github.com>
Date:   Sat Mar 14 00:08:50 2026 +0200

    Circle Drawing Algorithm changed

[33mcommit 9deb438ff622a5c3d021195c8f8f9f240e27cc59[m
Author: cevher kemal sirin <76917072+cevherkemalsirin@users.noreply.github.com>
Date:   Mon Mar 9 21:42:08 2026 +0200

    Create Screen class to render to the window

[33mcommit d62e5e0ab422b9c0b19c82e4c3860a1be1b33f9c[m
Author: cevher kemal sirin <76917072+cevherkemalsirin@users.noreply.github.com>
Date:   Sun Mar 8 17:47:56 2026 +0200

    Create Renderer2D to render Basic Shapes

[33mcommit 247e25ac6f78cd140cad31d361c53e3ea1c133e4[m
Author: cevher kemal sirin <76917072+cevherkemalsirin@users.noreply.github.com>
Date:   Sun Mar 8 13:11:16 2026 +0200

    Create and Add Geometric shape classes

[33mcommit c08b33ee8aa744a317c7dfbfea533d062006f729[m
Author: cevher kemal sirin <76917072+cevherkemalsirin@users.noreply.github.com>
Date:   Sun Mar 8 10:06:25 2026 +0200

    Add 2D Vector class and helper

[33mcommit d9cb3612a5b072404031779f8a33d49f291e8f0b[m
Author: cevher kemal sirin <76917072+cevherkemalsirin@users.noreply.github.com>
Date:   Sat Mar 7 23:11:07 2026 +0200

    Create Color and ScreenBuffer classes

[33mcommit b57210daa8798f3581b9c0acc3ee3303c1644ea9[m
Author: cevher kemal sirin <76917072+cevherkemalsirin@users.noreply.github.com>
Date:   Thu Feb 12 17:50:37 2026 +0200

    Create Main Loop(Fixed Deltatime)

[33mcommit 7ff8ab5c5aa9a882da0e244ad507d5d85972060e[m
Author: cevher kemal sirin <76917072+cevherkemalsirin@users.noreply.github.com>
Date:   Thu Feb 12 15:30:50 2026 +0200

    Create Application Class

[33mcommit da4079969bb1484986d245e783c3fae71342f969[m
Author: cevher kemal sirin <76917072+cevherkemalsirin@users.noreply.github.com>
Date:   Mon Feb 9 00:55:34 2026 +0200

    Create Project
