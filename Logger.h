class Logger{
    privatre:
        static std::ofstream logFile; // Static member variable to hold the log file stream
    public:
        static void log(const std::string& message); // Function to log a message
}