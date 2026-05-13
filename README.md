WAVE FUNCTION COLLAPSE

The wave function collapse sounds like a very intimidating algorithm. You might be inclined to think you have to graduate with a masters in physics to comprehend this wizardry but do not worry, this is actually a very simple algorithm!

For those of you who have never heard of the wave function collapse(or WFC) before, I'll give you a very short definition.
The goal is to insert a tileset like this: 

<img width="634" height="626" alt="image" src="https://github.com/user-attachments/assets/a8d662d3-8a47-439a-8894-6302414a486c" />

and then get this beautiful result:

<img width="607" height="613" alt="image" src="https://github.com/user-attachments/assets/a0e4aa87-817b-497e-8dbd-e440a0d6efb6" />

"Magic" some might say, but I like to think otherwise.

A vital part of this algorithm is defining neighbours!
let's take this tileset for example:

<img width="551" height="552" alt="image" src="https://github.com/user-attachments/assets/83a966f4-ccaa-4f52-9161-199f93195d1f" />

we want to generate a beautiful map consisting of these tiles. But not everything can be placed next to eachother! If we make a grid and just randomize tiles for each spot, this could be a result:

<img width="786" height="796" alt="image" src="https://github.com/user-attachments/assets/e0d9fda7-1218-46cb-9394-b7f092a5eb54" />

What a chaos! We certaintly don't want that. So instead, we will start to make some 'constraints' or 'connections' like I like to call them.

<img width="789" height="796" alt="image" src="https://github.com/user-attachments/assets/b93112ab-66ec-46cf-94c5-9482feeab479" />

Now we start to puzzle. for us it's clear that you can't have flying barrels in the map, but our computer doesn't know that yet.

<img width="758" height="124" alt="image" src="https://github.com/user-attachments/assets/eba6bfa4-d813-4a5c-84ff-e68569f7aed3" />

So for every possible tile, we make connections. We write down what neighbours a specific tile can have in each direction. It's *very* important that this get's mirrored;
If a lantern can be north of a barrel, the barrel can be south of the lantern.
Once you've done this correctly, the most difficult part is out of the way (I can speak of experience that taking out mistakes here is the most tedious part).

Great! Every tile has a neighbour now. So what is the next step?

<img width="556" height="553" alt="image" src="https://github.com/user-attachments/assets/4dae5502-07e3-43f6-9351-7820e476921f" />

We create a grid. Any spot since there are no restrictions yet, can be taken by any tile. Each spot has 16 possibilities or an enthropy of 16!
We speak of a high enthropy if the spot has many different tile options (here it has the max, 16).

Let's take this example:
<img width="552" height="553" alt="image" src="https://github.com/user-attachments/assets/7d4bd404-1ce7-46e7-9e6e-1807a51b1c8f" />

We picked a starting spot and filled it up with a random tile from the possibilities (this is all chance calculated).
Because this spot is filled now, the surrounding enthropy has changed. Take the north side for example.
We can put a barrel or a tree on top of it, maybe even a lantern or just air. What we can't do on the other hand, is put a rock right on top. That would look quite weird wouldn't it?

The best course of action here is to update the neighbours accordingly. I recommend each tile to have their own list of possibilities. Once their entrhopy changes, you update it!
<img width="1271" height="405" alt="image" src="https://github.com/user-attachments/assets/ba92e570-3770-447a-93ad-4b26725ab8d7" />

This way each tile is aware of what their options still are.

Now all that's left to do is to repeat this cycle. At the start, you should choose the tile with the lowest enthropy, this way you lower the chances of a conflicts. You collapse this tile by choosing a random tile number of the possibilities and set the spritesheet. You update the neighbours and voila. You can start all over again untill all the tiles have a possibility list with size 0.

I can already feel you looking at me with a suspicious look. And I have to admit, you're right. There are chances of a conflict.
As the algorithm does its job, there is a chance a tile is left empty, mostly because a tile hasn't collapsed yet, but due to it's neighbours, doesn't have any possibilities left to choose from.

There are 2 ways to solve this:

1) You can always backtrack and keep trying again, surely you'll get there at some point.
2) You discard all your changes and try again.
Depending on your tileset and expectations, one might fit you better than the other. In my case, since the chance of miscalculations are so small, I decided to go with the second option,

Now applying all of this to my project, here are some different results:

<img width="785" height="786" alt="image" src="https://github.com/user-attachments/assets/4a760421-544f-4e0e-9aa2-4b66c7e71353" />


<img width="789" height="886" alt="image" src="https://github.com/user-attachments/assets/52a7be0a-001d-42aa-8a57-1c757eb48a8f" />


<img width="789" height="785" alt="image" src="https://github.com/user-attachments/assets/326775b4-1995-4251-a0ff-67cc8762b8fc" />


<img width="787" height="886" alt="image" src="https://github.com/user-attachments/assets/60bcff48-43a2-4f0c-98ce-dc6c0484c02b" />


So you might think to yourself 'wow amazing' and you apply this method to any of your games. There is a big chance that you wish your map had more trees, or less rocks. That's fair.
And this is actually very achievable!

You can add weight to your tiles, so you can decide which ones will show up more frequently. If you decide to do this, it's very important that you calculate this in your enthropy:

// Sums are over the weights of each remaining
// allowed tile type for the square whose
// entropy we are calculating.
shannon_entropy_for_square =
  log(sum(weight)) -
  (sum(weight * log(weight)) / sum(weight))

See here an example by CodingQuest that added extra weight to the water tiles!

<img width="1321" height="740" alt="image" src="https://github.com/user-attachments/assets/afee6b7d-0e25-44b8-b353-ef448ca849de" />
 
I think it's very important to highlight that this method is not only limited to the 2d space. 
See here an example by Uproom games:

<img width="649" height="454" alt="image" src="https://github.com/user-attachments/assets/40a1976e-6188-40f7-af59-1fd6842e8a45" />

Or maybe even my favorite by Primarter:

<img width="831" height="473" alt="image" src="https://github.com/user-attachments/assets/13862fd1-0c70-4d0e-ab17-523de19dc575" />

If you decide to try to implement this algorithm, I recommend going though the sources listed below and to write most of your code down on paper first (such as I did myself).

Sources:
Wave - by Oskar Stålberg. (n.d.). https://oskarstalberg.com/game/wave/wave.html
CodingQuest. (2023, October 14). The Wave Function Collapse algorithm [Video]. YouTube. https://www.youtube.com/watch?v=qRtrj6Pua2A
The Wavefunction Collapse Algorithm explained very clearly | Robert Heaton. (2018, December 17). Robert Heaton. https://robertheaton.com/2018/12/17/wavefunction-collapse-algorithm/
Boris. (2025, February 28). Wave function collapse explained. BorisTheBrave.Com. https://www.boristhebrave.com/2020/04/13/wave-function-collapse-explained/
Boris. (2025b, February 28). Wave Function Collapse tips and tricks. BorisTheBrave.Com. https://www.boristhebrave.com/2020/02/08/wave-function-collapse-tips-and-tricks/
CodingQuest. (2023b, October 14). The Wave Function Collapse algorithm [Video]. YouTube. https://www.youtube.com/watch?v=qRtrj6Pua2A

Tileset:
Surt. (2015, October 16). Generic platformer Tiles. OpenGameArt.org. https://opengameart.org/content/generic-platformer-tiles
