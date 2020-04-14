#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot() : _image(new wxBitmap()) // constructor WITHOUT memory allocation
    {     
        // invalidate data handles
        _image = NULL;
        _chatLogic = nullptr;
        _rootNode = nullptr;
    }                    
    ChatBot(const std::string& filename) : _image(new wxBitmap(filename, wxBITMAP_TYPE_PNG))
    {
        _chatLogic = nullptr;
        _rootNode = nullptr;
    } // constructor WITH memory allocation
    
    ~ChatBot(){
        if(_image != NULL){
            delete _image;
            _image = NULL;
        }
    }

    ChatBot(ChatBot&& movedObj) : _image(movedObj._image)
    {
        movedObj._image = NULL;
    }

    ChatBot& operator=(const ChatBot& obj) {
        if (&obj != this) {
            delete _image;
            _image = NULL;
            _image = new wxBitmap();
            _image = obj._image;
        }

        return *this;
    }

    ChatBot& operator=(ChatBot&& obj) {
        if(&obj != this) {
            delete _image;
            _image = obj._image;
            obj._image = NULL;
        }

        return *this;
    }

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
    wxBitmap *GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */