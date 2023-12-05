#ifndef __COMMENTCELL_H__
#define __COMMENTCELL_H__

#include <gd.h>

namespace gd {

    class GJComment;

    class CommentCell : public TableViewCell, public LikeItemDelegate, public FLAlertLayerProtocol {
    public:
        PAD(4);
        GJComment* comment;
        bool accountComment;
    };

}

#endif
