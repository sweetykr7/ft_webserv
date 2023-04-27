#include <stdexcept>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#define PATH "cgiEnvSetting.sh"

static ssize_t	write_wrapper(int fd, const void* buf, size_t size);

int	main(int argc, char** argv, char** envp)
{
	int	fdset[2];
	int	pid;
	char	buf[1000000] = {'\0', };
	int		fileFd = open(PATH, O_RDONLY);
	struct stat	fileStatus;

	

	char**	envpTemp = envp;
	while (*envpTemp != NULL)
	{
		std::cout << *envpTemp << '\n';
		++envpTemp;
	}

	stat(PATH, &fileStatus);
	static_cast<void>(argc);
	static_cast<void>(argv);
	std::cout << "content length = " << fileStatus.st_size << '\n';
	setenv("CONTENT_LENGTH", std::to_string(fileStatus.st_size).c_str(), true);
	pipe(fdset);
	pid = fork();
	if (pid == 0)
	{
		close(fdset[0]);
		dup2(fileFd, STDIN_FILENO);
		dup2(fdset[1], STDOUT_FILENO);
		execve("./python-cgi.py", NULL, envp); //./cgi_tester
	}
	close(fdset[1]);

	ssize_t	count;
	std::string total_string = "";
	while ((count = read(fdset[0], buf, 10)) > 0)
	{
		std::cout << "output:" << buf << ", count:" << count << '\n';
		total_string = total_string + buf;
		::memset(buf, 0, count);
	}

	if (count < 0)
		throw std::runtime_error("read fail");

	if (0)
		write_wrapper(fdset[1], buf, 32768);

	std::cout << "total line : " << std::endl << total_string << std::endl;

	close(fdset[0]);
	wait(NULL);
}

static ssize_t	write_wrapper(int fd, const void* buf, size_t size)
{
	size_t			totalWriteBytes = 0;
	const uintptr_t	ptr = reinterpret_cast<const uintptr_t>(buf);

	while (size > 0)
	{
		void*	movedBuf = reinterpret_cast<void*>(ptr + totalWriteBytes);
		ssize_t	writeBytes = write(fd, movedBuf, size);

		if (writeBytes == -1)
			continue;
		totalWriteBytes += writeBytes;
		size -= writeBytes;
	}
	return totalWriteBytes;
}