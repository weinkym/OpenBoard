/*
 * Copyright (C) 2015-2022 Département de l'Instruction Publique (DIP-SEM)
 *
 * Copyright (C) 2013 Open Education Foundation
 *
 * Copyright (C) 2010-2013 Groupement d'Intérêt Public pour
 * l'Education Numérique en Afrique (GIP ENA)
 *
 * This file is part of OpenBoard.
 *
 * OpenBoard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License,
 * with a specific linking exception for the OpenSSL project's
 * "OpenSSL" library (or with modified versions of it that use the
 * same license as the "OpenSSL" library).
 *
 * OpenBoard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenBoard. If not, see <http://www.gnu.org/licenses/>.
 */




#ifndef UBSVGSUBSETADAPTOR_H_
#define UBSVGSUBSETADAPTOR_H_

#include <QtGui>
#include <QtXml>
#include <QGraphicsItem>

#include "frameworks/UBGeometryUtils.h"

class UBGraphicsSvgItem;
class UBGraphicsPolygonItem;
class UBGraphicsPixmapItem;
class UBGraphicsPDFItem;
class UBGraphicsWidgetItem;
class UBGraphicsMediaItem;
class UBGraphicsVideoItem;
class UBGraphicsAudioItem;
class UBGraphicsAppleWidgetItem;
class UBGraphicsW3CWidgetItem;
class UBGraphicsTextItem;
class UBGraphicsCurtainItem;
class UBGraphicsRuler;
class UBGraphicsAxes;
class UBGraphicsCompass;
class UBGraphicsProtractor;
class UBGraphicsScene;
class UBDocumentProxy;
class UBGraphicsStroke;
class UBPersistenceManager;
class UBGraphicsTriangle;
class UBGraphicsCache;
class UBGraphicsGroupContainerItem;
class UBGraphicsStrokesGroup;

class UBSvgSubsetAdaptor
{
    class UBSvgSubsetReader;
    private:

        UBSvgSubsetAdaptor() {;}
        virtual ~UBSvgSubsetAdaptor() {;}

    public:
        class UBSvgReaderContext
        {
        public:
            UBSvgReaderContext(std::shared_ptr<UBDocumentProxy> proxy, const QByteArray& pXmlData);
            ~UBSvgReaderContext();
            bool isFinished() const;
            void step();
            std::shared_ptr<UBGraphicsScene> scene() const;

        private:
            UBSvgSubsetReader* reader = nullptr;
        };

        static std::shared_ptr<UBGraphicsScene> loadScene(std::shared_ptr<UBDocumentProxy> proxy, const int pageIndex);
        static QByteArray loadSceneAsText(std::shared_ptr<UBDocumentProxy> proxy, const int pageIndex);
        static std::shared_ptr<UBGraphicsScene> loadScene(std::shared_ptr<UBDocumentProxy> proxy, const QByteArray& pArray);
        static std::shared_ptr<UBSvgReaderContext> prepareLoadingScene(std::shared_ptr<UBDocumentProxy> proxy, const int pageIndex);

        static void persistScene(std::shared_ptr<UBDocumentProxy> proxy, std::shared_ptr<UBGraphicsScene> pScene, const int pageIndex);
        static void upgradeScene(std::shared_ptr<UBDocumentProxy> proxy, const int pageIndex);

        static QUuid sceneUuid(std::shared_ptr<UBDocumentProxy> proxy, const int pageIndex);
        static void setSceneUuid(std::shared_ptr<UBDocumentProxy> proxy, const int pageIndex, QUuid pUuid);

        static void convertPDFObjectsToImages(std::shared_ptr<UBDocumentProxy> proxy);
        static void convertSvgImagesToImages(std::shared_ptr<UBDocumentProxy> proxy);

        static const QString nsSvg;
        static const QString nsXLink;
        static const QString nsXHtml;
        static const QString nsUb;
        static const QString xmlTrue;
        static const QString xmlFalse;

        static const QString sFontSizePrefix;
        static const QString sPixelUnit;
        static const QString sFontWeightPrefix;
        static const QString sFontStylePrefix;

    private:

        static QDomDocument loadSceneDocument(std::shared_ptr<UBDocumentProxy> proxy, const int pPageIndex);

        static QString uniboardDocumentNamespaceUriFromVersion(int fileVersion);

        static const QString sFormerUniboardDocumentNamespaceUri;

        static QString toSvgTransform(const QTransform& matrix);
        static QTransform fromSvgTransform(const QString& transform);


        class UBSvgSubsetReader
        {
            public:

                UBSvgSubsetReader(std::shared_ptr<UBDocumentProxy> proxy, const QByteArray& pXmlData);

                virtual ~UBSvgSubsetReader(){}

                std::shared_ptr<UBGraphicsScene> loadScene(std::shared_ptr<UBDocumentProxy> proxy);

                void start();
                bool isFinished();
                void processElement();
                std::shared_ptr<UBGraphicsScene> scene();

            private:

                UBGraphicsPolygonItem* polygonItemFromLineSvg(const QColor& pDefaultBrushColor);

                UBGraphicsPolygonItem* polygonItemFromPolygonSvg(const QColor& pDefaultBrushColor);

                QList<UBGraphicsPolygonItem*> polygonItemsFromPolylineSvg(const QColor& pDefaultColor);

                UBGraphicsPixmapItem* pixmapItemFromSvg();

                UBGraphicsSvgItem* svgItemFromSvg();

                UBGraphicsPDFItem* pdfItemFromPDF();

                UBGraphicsMediaItem* videoItemFromSvg();

                UBGraphicsMediaItem* audioItemFromSvg();

                UBGraphicsAppleWidgetItem* graphicsAppleWidgetFromSvg();

                UBGraphicsW3CWidgetItem* graphicsW3CWidgetFromSvg();

                UBGraphicsTextItem* textItemFromSvg();

                UBGraphicsCurtainItem* curtainItemFromSvg();

                UBGraphicsRuler* rulerFromSvg();

                UBGraphicsAxes* axesFromSvg();

                UBGraphicsCompass* compassFromSvg();

                UBGraphicsProtractor* protractorFromSvg();

                UBGraphicsTriangle* triangleFromSvg();

                UBGraphicsCache* cacheFromSvg();

                void readGroupRoot();
                QGraphicsItem *readElementFromGroup();
                UBGraphicsGroupContainerItem* readGroup();

                void graphicsItemFromSvg(QGraphicsItem* gItem);

                qreal normalizedZValue(bool* hasValue);

                QXmlStreamReader mXmlReader;
                int mFileVersion;
                std::shared_ptr<UBDocumentProxy> mProxy;
                QString mDocumentPath;

                QColor mGroupDarkBackgroundColor;
                QColor mGroupLightBackgroundColor;
                qreal mGroupZIndex;
                bool mGroupHasInfo;

                bool saveSceneAfterLoading;

                QString mNamespaceUri;
                std::shared_ptr<UBGraphicsScene> mScene;

                QHash<QString,UBGraphicsStrokesGroup*> mStrokesList;

                UBGraphicsStrokesGroup* strokesGroup = nullptr;
                UBGraphicsStroke* currentStroke = nullptr;
                UBGraphicsWidgetItem *currentWidget = nullptr;
                bool mMustFinalize = false;
        };

        class UBSvgSubsetWriter
        {
            public:

                UBSvgSubsetWriter(std::shared_ptr<UBDocumentProxy> proxy, std::shared_ptr<UBGraphicsScene> pScene, const int pageIndex);

                bool persistScene(std::shared_ptr<UBDocumentProxy> proxy, int pageIndex);

                virtual ~UBSvgSubsetWriter(){}

            private:

                void persistGroupToDom(QGraphicsItem *groupItem, QDomElement *curParent, QDomDocument *curDomDocument);
                void persistStrokeToDom(QGraphicsItem *strokeItem, QDomElement *curParent, QDomDocument *curDomDocument);
                void polygonItemToSvgPolygon(UBGraphicsPolygonItem* polygonItem, bool groupHoldsInfo);
                void polygonItemToSvgLine(UBGraphicsPolygonItem* polygonItem, bool groupHoldsInfo);
                void strokeToSvgPolyline(UBGraphicsStroke* stroke, bool groupHoldsInfo);
                void strokeToSvgPolygon(UBGraphicsStroke* stroke, bool groupHoldsInfo);

                inline QString pointsToSvgPointsAttribute(QVector<QPointF> points)
                {
                    UBGeometryUtils::crashPointList(points);

                    int pointsCount = points.size();
                    QString svgPoints;

                    int length = 0;
                    QString sBuf;

                    for(int j = 0; j < pointsCount; j++)
                    {
                        sBuf = "%1,%2 ";
                        const QPointF & point = points.at(j);

                        QString temp1 =  "%1", temp2 = "%2";

                        temp1 = temp1.arg(point.x());
                        temp2 = temp2.arg(point.y());

                        QLocale loc(QLocale::C);
                        sBuf = sBuf.arg(loc.toFloat(temp1)).arg(loc.toFloat(temp2));

                        svgPoints.insert(length, sBuf);
                        length += sBuf.length();
                    }
                    return svgPoints;
                }

                inline qreal trickAlpha(qreal alpha)
                {
                        qreal trickAlpha = alpha;
                        if(trickAlpha >= 0.2 && trickAlpha < 0.6){
                                trickAlpha /= 5;
                        }else if (trickAlpha < 0.8)
                            trickAlpha /= 3;

                        return trickAlpha;
                }

                void pixmapItemToLinkedImage(UBGraphicsPixmapItem *pixmapItem);
                void svgItemToLinkedSvg(UBGraphicsSvgItem *svgItem);
                void pdfItemToLinkedPDF(UBGraphicsPDFItem *pdfItem);
                void videoItemToLinkedVideo(UBGraphicsVideoItem *videoItem);
                void audioItemToLinkedAudio(UBGraphicsAudioItem *audioItem);
                void graphicsItemToSvg(QGraphicsItem *item);
                void graphicsAppleWidgetToSvg(UBGraphicsAppleWidgetItem *item);
                void graphicsW3CWidgetToSvg(UBGraphicsW3CWidgetItem *item);
                void graphicsWidgetToSvg(UBGraphicsWidgetItem *item);
                void textItemToSvg(UBGraphicsTextItem *item);
                void curtainItemToSvg(UBGraphicsCurtainItem *item);
                void rulerToSvg(UBGraphicsRuler *item);
                void axesToSvg(UBGraphicsAxes *item);
                void compassToSvg(UBGraphicsCompass *item);
                void protractorToSvg(UBGraphicsProtractor *item);
                void cacheToSvg(UBGraphicsCache* item);
                void triangleToSvg(UBGraphicsTriangle *item);
                void writeSvgElement(std::shared_ptr<UBDocumentProxy> proxy);

        private:

                std::shared_ptr<UBGraphicsScene> mScene;
                QXmlStreamWriter mXmlWriter;
                QString mDocumentPath;
                int mPageIndex;

        };
};

#endif /* UBSVGSUBSETADAPTOR_H_ */
