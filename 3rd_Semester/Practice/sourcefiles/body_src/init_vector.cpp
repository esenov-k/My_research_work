// Инициализация вектора состояния (px, py, vx, vy)
VectorXd x(4);
x << 0, 0, 0, 0;  // Начальное состояние

// Ковариационная матрица P
MatrixXd P = MatrixXd::Identity(4, 4) * 1000;  // Начальная неопределенность

// Матрица перехода состояния F
MatrixXd F = MatrixXd::Identity(4, 4);
double dt = 1.0;  // Временной шаг
F(0, 2) = dt;  // Связь px с vx
F(1, 3) = dt;  // Связь py с vy

// Матрица шума процесса Q
MatrixXd Q = MatrixXd::Zero(4, 4);
double noise_ax = 9.0, noise_ay = 9.0;
Q(0, 0) = Q(1, 1) = 0.5 * dt * dt * noise_ax;
Q(2, 2) = Q(3, 3) = dt * noise_ax;

// Матрица измерений для камеры (измерения px, py)
MatrixXd H_cam(2, 4);
H_cam << 1, 0, 0, 0,
         0, 1, 0, 0;

// Матрица измерений для радара
MatrixXd H_radar(2, 4);
H_radar << 1, 0, 0, 0,
           0, 1, 0, 0;

// Ковариации шума для камеры и радара
MatrixXd R_cam(2, 2);
R_cam << 0.01, 0,
         0, 0.01;

MatrixXd R_radar(2, 2);
R_radar << 0.1, 0,
           0, 0.1;