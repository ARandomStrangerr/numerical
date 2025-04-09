Numerical methods
# Gaussian Elimination:
Solving the system $Ax=b$ directly
i.e, given a system of equations:

$$
\begin{cases}
x_1 + x_2 + x_3 = 1\\
x_1 + 2x_2 + 4x_3 = -1\\
x_1 + 3x_2 + 9x_4 = 1
\end{cases}
$$

This can be written in matrix form $Ax=b$

$$
\left(
\begin{matrix}
1 & 1 & 1\\
1 & 2 & 4\\
1 & 3 & 9
\end{matrix}
\right)
\left(
\begin{matrix}
x_1\\
x_2\\
x_3
\end{matrix}
\right)=\left(
\begin{matrix}
1\\
-1\\
1
\end{matrix}
\right)
$$

Or agumented matrix

$$
\begin{matrix}
1 & 1 & 1 & | & 1\\
1 & 2 & 4 & | & -1\\
1 & 3 & 9 & | & 1
\end{matrix}
$$

For this case, there is nothing much to debate to talk about.

The real one that we need to notice is when there is a 0 on the diagonal.

To use the above algorim for GE, we must have diagonal coef $\not=$ 0; therefore, if any paricular diagonal coef = 0, we swap it to the bottom. however, swapping 2 rows cost O(n) operations. We could use a trick to swap 2 rows by having an index array to track which rows is what. It makes O(n) operation into O(1).

The thing we need to know about this that the execution of RRE is $O(n^3)$ and backward subsitution is $O(n^2)$

# Lower Upper Decomposition

Here we split an system $Ax=b \iff LUx = b$.

Then we let $Ux=y$ to solve the system: $Ly = b$ to obtain $y$ then solve $Ux=y$ to get $x$ as final answer

For matrix:

$$
\begin{matrix}
4 & 3 & -1\\
2 & -4 & 5\\
1 & 2 & 6
\end{matrix}
$$

Can be slit into LU:

$$
\left(
\begin{matrix}
1 & 0 & 0\\
-1/2 & 1 & 0\\
1/4 & -1/2 & 1
\end{matrix}
\right)
\left(
\begin{matrix}
4 &3 &-1\\
0 &-2.5 & 4.5\\
0 & 0 & 8.5
\end{matrix}
\right)
$$

from the example we can see the following:

**lower matrix** meanings that all the entries on the upper diagonal = 0 and entries on the diagonal = 1. $A_{ij} = 1$ for $i=j$ and $A_{ij} = 0$ for $i > j$.

**upper matrix** meaning that all the entries on the lower diagonal = 0. $A_{ij} = 0$ for $j < j$

**The entries of lower matrix** $= \frac{A_{i, diagonal}}{A_{diagona, diagonal}}$ for $i = diagonal + 1 \to$ end of rows

**The entries of upper marix** = - **entries of lower matrix** $\cdot A_{diagonal,j} + A_{i,j}$

Now, we can solve the matrix first with forward subsitution, then backward subsitution.

**First concern** memeory usage
we split the matrix into LU which double the memory usage. It is not neccessary the case because the uper matrix has all the lower index to be 0 and vice versa for the lower one, we can save memory by storing both of those matrix in one like the following:

$$
\left(
\begin{matrix}
4 &3 &-1\\
-1/2 &-2.5 & 4.5\\
1/4 & -1/2 & 8.5
\end{matrix}
\right)
$$

okay, people often say that LUD is better than GE in computation. Why?

At first glance, we see that Split A = LU takes $O(n^3)$ and backward + forward subsitution takes $O(2n^2)$

The coest of splitting is already as expensive as whole GE.

The saving grace comes from when we solving the same matrix A but with different b. This is when we get our avantages. we split it once taking $O(n^3)$ and consistently solving the matrix taking $O(n^2)$. Think of it as invest once, return later.
