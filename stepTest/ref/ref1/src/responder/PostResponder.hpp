#ifndef POSTRESPONDER_HPP
#define POSTRESPONDER_HPP

#include "responder/AResponder.hpp"

class	PostResponder : public AResponder
{
public:
// constructors & destructor
	PostResponder(RequestHandler& requestHandler);
	~PostResponder();

// operators
	PostResponder	&operator=(const PostResponder& postResponder);

// member functions
	virtual void	respondWork();
	// void			constructCgi(std::string& readBody);
	void			constructCgi();

private:
};

#endif
