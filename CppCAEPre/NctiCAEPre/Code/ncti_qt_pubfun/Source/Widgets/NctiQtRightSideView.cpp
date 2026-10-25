/*
 * Copyright (c) 2025 粤港澳大湾区（广东）国创中心
 *
 * This file is a part of NctiCAEPre.
 *
 * NctiCAEPre is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 */

#include "NctiQtRightSideView.h"

#include <QHBoxLayout>
#include <QToolButton>
#include <QVariant>

#include "NctiTreeSideBar.h"
#include "NctiTreeSidePannel.h"
#include "NctiQtPythonScriptEdit.h"  
#include "NctiObjectProperty.h"

#ifdef NCTI_ENABLE_AIQA_SERVICE
#include "NctiQtScriptExecutor.h"
#include <QWebChannel>
#include <QUrl>
#include "NctiQtWebPubFunDelegate.h"
#include "NctiQtWebView.h"
#include "NctiQtWebPubFun.h"
#include "NctiQtDbChatManager.h"
#endif

namespace NCTI
{
#ifdef NCTI_ENABLE_AIQA_SERVICE
    class NctiQtWebPubFunImpl : public NctiQtWebPubFunDelegate
    {
        friend class NctiQtRightSideView;
    public:
        NctiQtWebPubFunImpl(NctiQtRightSideView* pSideView) : q_ptr(pSideView) {}
        void setUrl(const QUrl& chat, const QUrl& fav);
        void setDbPath(const QString& path);
        NctiQtWebView* chatView();
        NctiQtWebView* favView();
        void updateFavView();
    protected:
        QVariantMap runScript(const QString& content) override;
        QVariantMap getChatMessage(int pageIndex, int countPerPage) override;
        QVariantMap saveChatMessage(const QVariantList& data) override;
        QVariantMap getChatFavorites(int pageIndex, int countPerPage) override;
        QVariantMap saveChatFavorites(const QVariantList& data) override;
        QWebChannel* webChannel();

    private:
        NctiQtRightSideView* q_ptr{ nullptr };
        QUrl m_ChatUrl;
        QUrl m_FavUrl;
        QString m_DbPath;
        NctiQtWebView* m_ChatView{ nullptr };
        NctiQtWebView* m_FavView{ nullptr };
        QWebChannel* m_WebChannel{ nullptr };
        NctiQtWebPubFun* m_WebPubFun{ nullptr };
    };

    void NctiQtWebPubFunImpl::setUrl(const QUrl& chat, const QUrl& fav)
    {
        m_ChatUrl = chat;
        m_FavUrl = fav;
        chatView()->setUrl(chat);
        favView()->setUrl(fav);
    }

    void NctiQtWebPubFunImpl::setDbPath(const QString& path)
    {
        m_DbPath = path;
    }

    NctiQtWebView* NctiQtWebPubFunImpl::chatView()
    {
        if (nullptr == m_ChatView) {
            m_ChatView = new NctiQtWebView(q_ptr);
            m_ChatView->page()->setWebChannel(webChannel());
            m_ChatView->setUrl(m_ChatUrl);
            m_WebPubFun->SetAiAssistentPage(m_ChatView->page());
        }
        return m_ChatView;
    }

    NctiQtWebView* NctiQtWebPubFunImpl::favView()
    {
        if (nullptr == m_FavView) {
            m_FavView = new NctiQtWebView(q_ptr);
            m_FavView->page()->setWebChannel(webChannel());
            m_FavView->setUrl(m_FavUrl);
            m_WebPubFun->SetCodeStorePage(m_FavView->page());
        }
        return m_FavView;
    }

    void NctiQtWebPubFunImpl::updateFavView()
    {
        m_WebPubFun->updateCodeStore();
    }

    QVariantMap NctiQtWebPubFunImpl::runScript(const QString& content)
    {
        q_ptr->editorView()->getExecutor()->excuteCommand(content);
        return NctiQtWebPubFun::createResult(1, "", QVariantMap());
    }

    QVariantMap NctiQtWebPubFunImpl::getChatMessage(int pageIndex, int countPerPage)
    {
        if (m_DbPath.isEmpty()) {
            return NctiQtWebPubFun::createResult(-1, "", QVariantMap());
        }
        NctiQtDbChatManager dbMgr(m_DbPath);
        auto data = dbMgr.getChatMessage(pageIndex, countPerPage);
        return NctiQtWebPubFun::createResult(1, "", data);
    }

    QVariantMap NctiQtWebPubFunImpl::saveChatMessage(const QVariantList& data)
    {
        if (m_DbPath.isEmpty()) {
            return NctiQtWebPubFun::createResult(-1, "", QVariantMap());
        }
        NctiQtDbChatManager dbMgr(m_DbPath);
        auto res = dbMgr.saveChatMessage(data);
        return NctiQtWebPubFun::createResult(res ? 1 : -1, "", QVariantMap());
    }

    QVariantMap NctiQtWebPubFunImpl::getChatFavorites(int pageIndex, int countPerPage)
    {
        if (m_DbPath.isEmpty()) {
            return NctiQtWebPubFun::createResult(-1, "", QVariantMap());
        }
        NctiQtDbChatManager dbMgr(m_DbPath);
        auto data = dbMgr.getChatFavorites(pageIndex, countPerPage);
        return NctiQtWebPubFun::createResult(1, "", data);
    }

    QVariantMap NctiQtWebPubFunImpl::saveChatFavorites(const QVariantList& data)
    {
        if (m_DbPath.isEmpty()) {
            return NctiQtWebPubFun::createResult(-1, "", QVariantMap());
        }
        NctiQtDbChatManager dbMgr(m_DbPath);
        auto res = dbMgr.saveChatFavorites(data);
        return NctiQtWebPubFun::createResult(res ? 1 : -1, "", QVariantMap());
    }

    QWebChannel* NctiQtWebPubFunImpl::webChannel()
    {
        if (nullptr == m_WebChannel) {
            m_WebChannel = new QWebChannel(q_ptr);
            m_WebPubFun = new NctiQtWebPubFun(m_WebChannel);
            m_WebPubFun->setDelegate(this);
            m_WebChannel->registerObject("qtObject", m_WebPubFun);
        }
        return m_WebChannel;
    }
#endif

    NctiQtRightSideView::NctiQtRightSideView(QWidget* parent)
        : QFrame(parent)
    {
#ifdef NCTI_ENABLE_AIQA_SERVICE
        m_WebPubFunImpl = std::make_unique<NctiQtWebPubFunImpl>(this);
#endif
        setupUi();
    }

    NctiQtRightSideView::~NctiQtRightSideView()
    {

    }

    NctiQtPythonScriptEdit* NctiQtRightSideView::editorView()
    {
        if (nullptr == m_EditerView) {
            m_EditerView = new NctiQtPythonScriptEdit(this);
        }
        return m_EditerView;
    }

    NctiObjectProperty* NctiQtRightSideView::propertyView()
    {
        if (nullptr == m_PropertyView) {
            m_PropertyView = new NctiObjectProperty(this);
        }
        return m_PropertyView;
    }

    void NctiQtRightSideView::hideScriptEditor()
    {
        if (m_SideBar->getCurrentIndex() == ViewEditor) {
            auto button = m_SideBar->getButtonByObjName("sidebar_script_editor");
            button->setChecked(false);
            m_SideBar->sigButtonClicked(button);
        }
    }

    void NctiQtRightSideView::changeCurrentView(View view)
    {
        m_SideBar->setCurrentIndex(view);
        m_SidePanel->show();
        m_SidePanel->setCurrentIndex(view);
        Q_EMIT sigSidePanelVisible(view, true);
    }

    NctiQtRightSideView::View NctiQtRightSideView::currentView()
    {
        if (m_SidePanel->isHidden()) {
            return NctiQtRightSideView::View(-1);
        }
        return NctiQtRightSideView::View(m_SideBar->getCurrentIndex());
    }

    void NctiQtRightSideView::setUrl(const QUrl& chat, const QUrl& fav)
    {
#ifdef NCTI_ENABLE_AIQA_SERVICE
        m_WebPubFunImpl->setUrl(chat, fav);
#endif
    }

    void NctiQtRightSideView::setDbPath(const QString& path)
    {
#ifdef NCTI_ENABLE_AIQA_SERVICE
        m_WebPubFunImpl->setDbPath(path);
#endif
    }

    void NctiQtRightSideView::updateFavView()
    {
#ifdef NCTI_ENABLE_AIQA_SERVICE
        m_WebPubFunImpl->updateFavView();
#endif
    }

    void NctiQtRightSideView::setupUi()
    {
        auto hBoxLayout = new QHBoxLayout(this);
        hBoxLayout->setContentsMargins(0, 0, 0, 0);
        hBoxLayout->setSpacing(0);

        m_SideBar = new NctiTreeSideBar(this);
        m_SideBar->setObjectName("objTreeSidebar");
        m_SideBar->setContentsMargins(0, 0, 0, 0);
        m_SideBar->setFixedWidth(40);
        m_SideBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

        m_SidePanel = new NctiTreeSidePanel(this);
        m_SidePanel->setContentsMargins(0, 0, 0, 0);
        m_SidePanel->setObjectName("objTreeSidePanel");

        QFrame* separator = new QFrame(this);
        separator->setFrameShape(QFrame::VLine);
        separator->setFixedWidth(1);
        separator->setObjectName(QStringLiteral("objTree_separator"));
        separator->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

        hBoxLayout->addWidget(m_SidePanel);
        hBoxLayout->addWidget(separator);
        hBoxLayout->addWidget(m_SideBar);

        setLayout(hBoxLayout);
        m_SideBar->setSidePanel(m_SidePanel);
        m_SideBar->addSideButton(QIcon(":/Tree/script_editor.svg"), "sidebar_script_editor", editorView(), static_cast<int>(ViewEditor));
        m_SideBar->addSideButton(QIcon(":/Tree/property.svg"), "sidebar_property", propertyView(), static_cast<int>(ViewProperty));
#ifdef NCTI_ENABLE_AIQA_SERVICE
        m_SideBar->addSideButton(QIcon(":/Tree/chat.svg"), "sidebar_chat", m_WebPubFunImpl->chatView(), static_cast<int>(ViewChat));
        m_SideBar->addSideButton(QIcon(":/Tree/fav.svg"), "sidebar_fav", m_WebPubFunImpl->favView(), static_cast<int>(ViewFav));
#endif
        connect(m_SideBar, &NctiTreeSideBar::sigButtonClicked, this, &NctiQtRightSideView::onSideButtonClicked);
        m_SideBar->setCurrentIndex(0);
    }

    void NctiQtRightSideView::onSideButtonClicked(QToolButton* clickedButton)
    {
        if (!clickedButton) { return; }
        bool checked = clickedButton->isChecked();
        int id = clickedButton->property("sidePanelId").toInt();
        int index = clickedButton->property("sidePanelIndex").toInt();
        bool otherBtnChecked = m_SideBar->uncheckOtherButtons(clickedButton);
        
        if (checked) {
            if (m_SidePanel) {
                m_SidePanel->setVisible(true);
                Q_EMIT sigSidePanelVisible(id, true);
                if (index != m_SidePanel->currentIndex()) {
                    m_SidePanel->setCurrentIndex(index);
                }
            }
        }
        else {
            if (!otherBtnChecked && m_SidePanel) {
                m_SidePanel->setVisible(false);
                Q_EMIT sigSidePanelVisible(id, false);
            }
        }
    }
}