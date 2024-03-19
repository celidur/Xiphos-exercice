# Use a Debian slim image as the base to reduce size while maintaining glibc compatibility
FROM debian:bullseye-slim as builder

# Install g++ and make
RUN apt-get update && \
    apt-get install -y \
    g++ \
    make \
    && apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Set the working directory in the Docker image
WORKDIR /app

# Copy your source code into the Docker image
COPY . .

# Build your application
RUN make

# Start from a clean Debian slim image to run your application
FROM debian:bullseye-slim

# Install any runtime libraries your application might need
RUN apt-get update && \
    apt-get install -y \
    libstdc++6 \
    git \
    && apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Copy the built binaries and entrypoint script from the builder stage
COPY --from=builder /app/server /app/server
COPY --from=builder /app/client /app/client
COPY --from=builder /app/.git /app/.git
COPY --from=builder /app/entrypoint.sh /app/entrypoint.sh

# Set the working directory in the Docker image
WORKDIR /app

# Ensure the entrypoint script is executable
RUN chmod +x /app/entrypoint.sh

# Set the entrypoint script as the default way to run the container
ENTRYPOINT ["/app/entrypoint.sh"]

# Default command, can be overridden by passing arguments to docker run
CMD ["server", "/tmp/server.sock"]
