Numerical method
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

The real one that we need to notice is when there is a 0 on the diagonal
