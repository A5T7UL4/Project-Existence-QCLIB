Project Existence was started in dire hopes to just start with some project. Yet it was also aimed to make something meaningful that may have use someday.


In quantum information theory and quantum computing, validating theoretical calculations requires robust numerical tools capable of performing complex linear algebra, operator transformations, and quantum state evolutions. QCLIB is a lightweight, low-dependency C++ library designed to bridge the gap between manual symbolic calculations and computational verification. Built upon a custom std::pair<double, double> primitive representation for complex arithmetic, the framework eliminates reliance on external numerical suites while offering full transparency and precision in complex vector space computations.

The library is organized into three core computational modules:

1. Core Complex Linear Algebra: Provides foundational operators including Hermitian adjoints (𝐴†), matrix multiplication, dynamic tensor products (𝐴⊗𝐵), trace operations, and inner/outer vector products.

2. Spectral Analysis & Eigensystem Solver: Features an 𝑂(𝑛3) implicit QR decomposition algorithm equipped with Wilkinson and exceptional shifts, preceded by Householder reduction to upper Hessenberg form. This provides numerical convergence for complex eigenvalue extraction and spectral projector synthesis (𝑃𝜆).

3. Quantum Mechanics & Information Engine: Implements density matrix verification (Tr(𝜌)=1,𝜌≥0), state purity classification (pure vs. mixed states), unitary time evolution (𝜌→𝑈𝜌𝑈†), projective measurement collapse with probability normalization (𝑃𝑚𝜓/𝑝𝑚), and multi-partite composite system modeling through recursive tensor product aggregation.

QCLIB serves as a transparent computational tool for students, researchers, and developers to simulate, model, and verify multi-qubit quantum protocols, state evolutions, and measurement statistics.
