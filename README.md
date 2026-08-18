# WAVE FUNCTION COLLAPSE

The wave function collapse is a constraint-solving algorithms. This means that the algorithm will solve itself following specific defined rules. In this case it is used for procedural generation. So by defining specific rules and using randomization you can 
change generated tiles from this:

<img  height="500" alt="image" src="https://github.com/user-attachments/assets/a8d662d3-8a47-439a-8894-6302414a486c" />

to this by defining rules:

<img  height="500" alt="image" src="https://github.com/user-attachments/assets/a0e4aa87-817b-497e-8dbd-e440a0d6efb6" />

This outcome is achievable only through the formal definition of neighbor relationships.

## Neighbours

let's take this tileset for example:

<img height="500" alt="image" src="https://github.com/user-attachments/assets/83a966f4-ccaa-4f52-9161-199f93195d1f" />

we want to generate a map consisting of these tiles. But not everything can be placed next to eachother. If we make a grid and just randomize tiles for each spot, this could be a result:

<img  height="500" alt="image" src="https://github.com/user-attachments/assets/e0d9fda7-1218-46cb-9394-b7f092a5eb54" />

To get a closer result ot what we were expecting,  we will start to make some 'constraints' or 'connections'.

<img  height="500" alt="image" src="https://github.com/user-attachments/assets/b93112ab-66ec-46cf-94c5-9482feeab479" />

Now we start to puzzle. For us it's clear that you can't have flying barrels in the map, but our computer doesn't know that yet.

<img  height="500" alt="image" src="https://github.com/user-attachments/assets/eba6bfa4-d813-4a5c-84ff-e68569f7aed3" />

So for every possible tile, we make connections. We write down what neighbours a specific tile can have in each direction. It's *very* important that this get's mirrored;
If a lantern can be north of a barrel, the barrel can be south of the lantern.
Once you've done this correctly, the most difficult part is out of the way.

## Enthropy

<img  height="500" alt="image" src="https://github.com/user-attachments/assets/4dae5502-07e3-43f6-9351-7820e476921f" />

We create a grid. Any spot since there are no restrictions yet, can be taken by any tile. Each spot has 16 possibilities or an enthropy of 16!
We speak of a high enthropy if the spot has many different tile options (here it has the max, 16).

Let's take this example:

<img  height="500" alt="image" src="https://github.com/user-attachments/assets/7d4bd404-1ce7-46e7-9e6e-1807a51b1c8f" />

We picked a starting spot and filled it up with a random tile from the possibilities (this is all chance calculated).
Because this spot is filled now, the surrounding enthropy has changed. Take the north side for example.
We can put a barrel or a tree on top of it, maybe even a lantern or just air. What we can't do on the other hand, is put a rock right on top.

The best course of action here is to update the neighbours accordingly. I recommend each tile to have their own list of possibilities. Once their entrhopy changes, you update it!
<img  height="500" alt="image" src="https://github.com/user-attachments/assets/ba92e570-3770-447a-93ad-4b26725ab8d7" />

This way each tile is aware of what their options still are.

## The loop

Now all that's left to do is to repeat this cycle. At the start, you should choose the tile with the lowest enthropy, this way you lower the chances of conflicts. You collapse this tile by choosing a random tile number of the possibilities and set the spritesheet. You update the neighbours and the basics are done. You can start all over again untill all the tiles have a possibility list with size 0.

Something to be wary about are the chances of a conflict.
As the algorithm does its job, there is a chance a tile is left empty, mostly because a tile hasn't collapsed yet, but due to it's neighbours, doesn't have any possibilities left to choose from.

There are 2 ways to solve this:

1) You can always backtrack and regenerate the rest of the tiles untill all the tiles habe collapsed.
   
2) You discard all your changes and try again. Depending on your tileset and expectations, one might fit you better than the other.
   In my case, since the chance of miscalculations are so small, I decided to go with the second option.

Now applying all of this to my project, here are some different results:

<img  height="500" alt="image" src="https://github.com/user-attachments/assets/4a760421-544f-4e0e-9aa2-4b66c7e71353" />


<img height="500" alt="image" src="https://github.com/user-attachments/assets/52a7be0a-001d-42aa-8a57-1c757eb48a8f" />


<img  height="500" alt="image" src="https://github.com/user-attachments/assets/326775b4-1995-4251-a0ff-67cc8762b8fc" />


<img  height="500" alt="image" src="https://github.com/user-attachments/assets/60bcff48-43a2-4f0c-98ce-dc6c0484c02b" />


#Added functionality

The project has now a speed variable, which the user can interact with. This way you can see the wave function collapse unfold and which tiles get picked in which order!


## Variations
To further customize generation, such as increasing the frequency of trees or decreasing the appearance of rocks, you can implement tile weights. 
By assigning weights, you can control which tiles are more likely to be selected during the collapse phase.

If you decide to do this, it's very important that you make your calculations using the shannon-enthropy formula:

// Sums are over the weights of each remaining

// allowed tile type for the square whose

// entropy we are calculating.

shannon_entropy_for_square =
  log(sum(weight)) -
  (sum(weight * log(weight)) / sum(weight))

See here an example by CodingQuest that added extra weight to the water tiles!

<img  height="500" alt="image" src="https://github.com/user-attachments/assets/afee6b7d-0e25-44b8-b353-ef448ca849de" />
 
I think it's very important to highlight that this method is not only limited to the 2d space. 
See here an example by Uproom games:

<img  height="500" alt="image" src="https://github.com/user-attachments/assets/40a1976e-6188-40f7-af59-1fd6842e8a45" />

Or maybe even my favorite by Primarter:

<img  height="500" alt="image" src="https://github.com/user-attachments/assets/13862fd1-0c70-4d0e-ab17-523de19dc575" />

If you decide to try to implement this algorithm, I recommend going though the sources listed below and to write most of your code down on paper first (such as I did myself).


# Sources:
Wave - by Oskar Stålberg. (n.d.). https://oskarstalberg.com/game/wave/wave.html


CodingQuest. (2023, October 14). The Wave Function Collapse algorithm [Video]. YouTube. https://www.youtube.com/watch?v=qRtrj6Pua2A


The Wavefunction Collapse Algorithm explained very clearly | Robert Heaton. (2018, December 17). Robert Heaton. https://robertheaton.com/2018/12/17/wavefunction-collapse-algorithm/


Boris. (2025, February 28). Wave function collapse explained. BorisTheBrave.Com. https://www.boristhebrave.com/2020/04/13/wave-function-collapse-explained/


Boris. (2025b, February 28). Wave Function Collapse tips and tricks. BorisTheBrave.Com. https://www.boristhebrave.com/2020/02/08/wave-function-collapse-tips-and-tricks/


CodingQuest. (2023b, October 14). The Wave Function Collapse algorithm [Video]. YouTube. https://www.youtube.com/watch?v=qRtrj6Pua2A


Tileset:
Surt. (2015, October 16). Generic platformer Tiles. OpenGameArt.org. https://opengameart.org/content/generic-platformer-tiles
