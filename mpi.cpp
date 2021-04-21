/*#include <mpi.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

void sleep(int s) {
    std::this_thread::sleep_for(std::chrono::seconds(s));
}

int main() {
    MPI_Init(nullptr, nullptr);

    int num_processes;
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size = 3;
    std::vector<double> local_data(size);
        local_data[0] = 1;
        local_data[1] = 2;
        local_data[2] = 3;

    std::vector<double> recv_data;
    if (rank == 0) {
        recv_data.resize(size * num_processes);
    }

    // int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    //                void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    //                MPI_Comm comm)
    MPI_Gather(local_data.data(), local_data.size(), MPI_DOUBLE,
               recv_data.data(), local_data.size(), MPI_DOUBLE,
               //                ^^^^^^^^^^^^^^^^^ size of a single send
               0, MPI_COMM_WORLD);
    //         ^ rank of receiving process

    std::cout << "\n";
    for (auto v : recv_data) {
        std::cout << "rank: " << rank << " " << v << ' ';
    }
    std::cout << '\n';

    MPI_Finalize();
}

/*
#include <mpi.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

void sleep(int s) {
    std::this_thread::sleep_for(std::chrono::seconds(s));
}

int main() {
    MPI_Init(nullptr, nullptr);

    int num_processes;
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int> send;
    std::vector<int> receive;

    if (rank == 0) {
        receive.resize(num_processes);
    }
    if (rank == 1) {
        send.push_back(1);
    }
    if (rank == 2) {
        send.push_back(2);
    }
    if (rank == 3) {
        send.push_back(3);
    }
   if (rank != 0) std::cout << "\n rank: " << rank << " send: " << send[0] << "\n";
    // int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    //                void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    //                MPI_Comm comm)
    MPI_Gather(send.data(), send.size(), MPI_INT, receive.data(), send.size(), MPI_INT, 0, MPI_COMM_WORLD);
    //         ^ rank of receiving process
    
    if (rank == 0) {
    std::cout << "\n";
    for (auto v : receive) {
        std::cout << v << ' ';
    }
    std::cout << '\n';
    }
    MPI_Finalize();
}*/